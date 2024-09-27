#include <algorithm>
#include <iostream>
#include <random>

using namespace std;

string getRandomString(size_t length) {
  string result(length, 0);

  static const string alphastring = "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

  static random_device rd;
  static mt19937 gen{rd()};
  static uniform_int_distribution<> charid(0, alphastring.size() - 1);

  auto generator = []() -> char {
    return alphastring.at(charid(gen));
  };

  generate_n(result.begin(), length, generator);
  return result;
}

int main() {
  for (auto i = 5; i--;)
    cout << getRandomString(5) << endl;
  return 0;
}