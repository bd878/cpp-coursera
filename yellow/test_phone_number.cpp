#include "test_runner.h"
#include "phone_number.h"

void ParsesCorrectPhone() {
  for (int i = 10; i > 1; --i) {
    string country_code = GetRandomString(i);
    string city_code = GetRandomString(i);
    string phone_number = GetRandomString(i) + '-' + GetRandomString(i);

    string international_phone_number = '+' + country_code + '-' + city_code + '-' + phone_number;
    PhoneNumber phone(international_phone_number);
    AssertEqual(phone.GetCountryCode(), country_code, "Parses country code");
    AssertEqual(phone.GetCityCode(), city_code, "Parses city code");
    AssertEqual(phone.GetLocalNumber(), phone_number, "Parses phone number");
    AssertEqual(phone.GetInternationalNumber(), international_phone_number, "Keeps international phone number");
  }
}

int main() {
  TestRunner runner;

  runner.RunTest(ParsesCorrectPhone, "ParsesCorrectPhone");

  return 0;
}