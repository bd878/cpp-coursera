#pragma once

#include <string>

using namespace std;

class PhoneNumber {
public:
  /* Принимает строку в формате +XXX-YYY-ZZZZZZ
     Часть от '+' до первого '-' - это код страны.
     Часть между первым и вторым символами '-' - код города
     Всё, что идёт после второго символа '-' - местный номер.
     Код страны, код города и местный номер не должны быть пустыми.
     Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.

     Примеры:
     * +7-495-111-22-33
     * +7-495-1112233
     * +323-22-460002
     * +1-2-coursera-cpp
     * 1-2-333 - некорректный номер - не начинается на '+'
     * +7-1233 - некорректный номер - есть только код страны и города
  */
  explicit PhoneNumber(const string &international_number);

  string GetCountryCode() const { return country_code_; };
  string GetCityCode() const { return city_code_; };
  string GetLocalNumber() const { return local_number_; };
  string GetInternationalNumber() const { return '+' + country_code_ + '-' + city_code_ + '-' + local_number_; };

private:
  string country_code_;
  string city_code_;
  string local_number_;
};
