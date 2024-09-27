#include <string>
#include <memory>
#include <utility>
#include <iostream>

using namespace std;

struct Email {
  string from;
  string to;
  string message;

  explicit Email(string f, string t, string m)
    : from(f), to(t), message(m)
  {
    cout << "I created\n";
  };

  Email(Email&& other) {
    cout << "I moved" << '\n';
    from = move(other.from);
    to = move(other.to);
    message = move(other.message);
  }

  Email(Email& other) {
    cout << "I copy constructed\n";
    from = other.from;
    to = other.to;
    message = other.message;
  }

  ~Email() {
    cout << "I destroyed\n";
  }

  friend ostream& operator<<(ostream& os, const Email& mail) {
    os << mail.from << ' ' << mail.to << ' ' << mail.message << '\n';
    return os;
  }
};

class Postman {
private:
  Email mail; // unique_ptr<Email> mail;
public:
  Postman(string f, string t, string m)
    : mail(f, t, m) {};

  Email GetMail() {
    return mail;
  }
};

int main() {
  cout << "Start main\n";

  {
    Postman post("richard@stallman.gov.uk", "kalvin@harris.com", "Keep rolling!");

    Email mail = post.GetMail();
    cout << mail;
  }

  cout << "Stop main\n";

  return 0;
}