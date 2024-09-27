#include <sstream>
#include <stdexcept>
#include <string>

#include "phone_number.h"

PhoneNumber::PhoneNumber(const string& international_number) {
  stringstream ss{international_number};

  string* buffer = new string;
  char ch = '+';
  while (getline(ss, *buffer, ch)) {
    if (ch == '+') {
      ch = '-';
      buffer = &country_code_;
      continue;
    }

    if (ch == '-' && buffer == &country_code_) {
      buffer = &city_code_;
      continue;
    }

    if (ch == '-' && buffer == &city_code_) {
      ch = ' ';
      buffer = &local_number_;
      continue;
    }
  }

  if (country_code_.empty() || city_code_.empty() || local_number_.empty()) {
    throw invalid_argument("wrong phone number " + international_number);
  }
}
