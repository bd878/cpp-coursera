#include "test_runner.h"
#include <functional>
#include <utility>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


struct Email {
  string from;
  string to;
  string body;

  Email(string f, string t, string b)
    : from(f), to(t), body(b) {};
};


class Worker {
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // только первому worker-у в пайплайне нужно это имплементировать
    throw logic_error("Unimplemented");
  }

protected:
  unique_ptr<Worker> next;

  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
  void PassOn(unique_ptr<Email> email) const {
    if (next) {
      next->Process(move(email));
    }
  }

public:
  void SetNext(unique_ptr<Worker> worker) {
    if (next) {
      next->SetNext(move(worker));
    } else {
      next = move(worker);
    }
  }
};


class Reader : public Worker {
private:
  istream& is;
public:
  explicit Reader(istream& in) : is(in) {}

  void Run() {
    string from, to, body;

    while (
      getline(is, from) && !from.empty() &&
      getline(is, to) && !to.empty() &&
      getline(is, body) && !body.empty()
    ) {
      PassOn(make_unique<Email>(from, to, body));
    }
  }

  virtual void Process(unique_ptr<Email> email) {
    throw logic_error("Unimplemented");
  }
};


class Filter : public Worker {
public:
  using Function = function<bool(const Email&)>;
private:
  Function predicate;
public:
  explicit Filter(Function f) : predicate(move(f)) {};

  void Process(unique_ptr<Email> email) {
    if (predicate(*(email.get()))) {
      PassOn(move(email));
    }
  }
};


class Copier : public Worker {
private:
  string receiver;
public:
  explicit Copier(string mail) : receiver(mail) {};

  void Process(unique_ptr<Email> email) {
    unique_ptr<Email> copy = make_unique<Email>(
      email.get()->from,
      receiver,
      email.get()->body
    );

    if (email.get()->to != receiver) {
      PassOn(move(email));
      PassOn(move(copy));
    } else {
      PassOn(move(email));
    }
  }
};


class Sender : public Worker {
private:
  ostream& os;
public:
  explicit Sender(ostream& out) : os(out) {}

  void Process(unique_ptr<Email> email) {
    Email* mail = email.get();

    os << mail->from << '\n'
      << mail->to << '\n'
      << mail->body << '\n';

    PassOn(move(email));
  }
};


// реализуйте класс
class PipelineBuilder {
private:
  unique_ptr<Reader> first;
public:
  // добавляет в качестве первого обработчика Reader
  explicit PipelineBuilder(istream& in)
    : first(make_unique<Reader>(in)) {}

  // добавляет новый обработчик Filter
  PipelineBuilder& FilterBy(Filter::Function filter) {
    first->SetNext(make_unique<Filter>(move(filter)));
    return *this;
  }

  // добавляет новый обработчик Copier
  PipelineBuilder& CopyTo(string recipient) {
    first->SetNext(make_unique<Copier>(recipient));
    return *this;
  }

  // добавляет новый обработчик Sender
  PipelineBuilder& Send(ostream& out) {
    first->SetNext(make_unique<Sender>(out));
    return *this;
  }

  // возвращает готовую цепочку обработчиков
  unique_ptr<Worker> Build() {
    return move(first);
  }
};

void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );

  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}
