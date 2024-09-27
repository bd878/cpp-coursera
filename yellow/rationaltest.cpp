#include <iostream>
#include <random>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

class Rational {
private:
  int num;
  int denom;
public:
  // Вы можете вставлять сюда различные реализации,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный

  Rational(): num{0}, denom{1} {};
  Rational(int numerator, int denominator) {
  }

  int Numerator() const {
    return 0;
  }

  int Denominator() const {
    return 1;
  }
};

int GetRandomInt(int from, int to) {
  static random_device rd;
  static mt19937 gen{rd()};
  static uniform_int_distribution<> randint(from, to);
  return randint(gen);
}

pair<int, int> RandomTrueRational(int from = 1, int to = 100) {
  int randint = GetRandomInt(from, to);
  return {randint + 1, randint};
}

pair<int, int> RandomShortableRational(int fraction = 2, int from = 1, int to = 100) {
  int randint = GetRandomInt(from, to);
  return {randint, randint * fraction};
}

void DefaultConstructor() {
  Rational r;
  Assert(r.Numerator() == 0 && r.Denominator() == 1, "Default constructor");
}

void InitializedConstructor() {
  Rational z(0, GetRandomInt(2, 100));
  Assert(z.Numerator() == 0 && z.Denominator() == 1, "Zero numerator leads to default constructor");

  for (int i = 10; i--;) {
    auto [n1, n2] = RandomTrueRational();
    Rational r1(n1, n2);
    Assert(r1.Numerator() == n1 && r1.Denominator() == n2, "True rational");

    auto [m1, m2] = RandomShortableRational(2);
    Rational r2(m1, m2);
    Assert(r2.Numerator() == 1 && r2.Denominator() == 2, "Rational is shortened");
  }
}

void NegativeRational() {
  for (int i = 10; i--;) {
    int num = GetRandomInt(-10, -1);
    int denom = GetRandomInt(1, 10);
    Rational r(num, denom);
    Assert(r.Numerator() < 0 && r.Denominator() > 0, "Negative numerator positive denominator");

    int negative_denom = GetRandomInt(-100, -10);
    Rational r2(num, negative_denom);
    Assert(r2.Numerator() > 0 && r2.Denominator() > 0, "Negative numerator and denominator gives positive rational");

    int positive_num = GetRandomInt(1, 100);
    Rational r3(positive_num, negative_denom);
    Assert(r3.Numerator() < 0 && r3.Denominator() > 0, "Positive numerator and negative denominator gives negative numerator and positive denominator");
  }
}

int main() {
  TestRunner runner;

  runner.RunTest(DefaultConstructor, "DefaultConstructor");
  runner.RunTest(InitializedConstructor, "InitializedConstructor");
  runner.RunTest(NegativeRational, "NegativeRational");

  return 0;
}
