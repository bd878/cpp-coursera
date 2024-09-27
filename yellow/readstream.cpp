#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

int main() {
  stringstream ss{"7-917-710-29-78"};

  string country_code;
  string city_code;
  string phone;

  string* buffer = new string;
  char ch = '+';
  while (getline(ss, *buffer, ch)) {
    if (ch == '+') {
      ch = '-';
      buffer = &country_code;
      continue;
    }

    if (ch == '-' && buffer == &country_code) {
      buffer = &city_code;
      continue;
    }

    if (ch == '-' && buffer == &city_code) {
      ch = ' ';
      buffer = &phone;
      continue;
    }
  }

  if (country_code.empty() || city_code.empty() || phone.empty()) {
    throw invalid_argument("wrong phone number");
  }

  return 0;
}
