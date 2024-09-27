#include <iostream>
#include <string>

using namespace std;

class INotifier {
public:
  virtual void Notify(const string& message) = 0;
};

class SmsNotifier : public INotifier {
private:
  string phone;
public:
  SmsNotifier(const string& number): phone(number) {};
  void Notify(const string& message) {
    SendSms(phone, message);
  }
};

class EmailNotifier : public INotifier {
private:
  string email;
public:
  EmailNotifier(const string& str): email(str) {};
  void Notify(const string& message) {
    SendEmail(email, message);
  }
};
