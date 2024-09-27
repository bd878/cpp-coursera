#include "test_runner.h"

int GetRandomInt(int from, int to) {
  random_device rd;
  mt19937 gen{rd()};
  uniform_int_distribution<> randint(from, to);
  return randint(gen);
}

long long int GetRandomLongInt(long long int from, long long int to) {
  static random_device rd;
  static mt19937 gen{rd()};
  static uniform_int_distribution<> randlonglong(from, to);
  return randlonglong(gen); 
}

double GetRandomDouble(double from, double to) {
  static random_device rd;
  static mt19937 gen{rd()};
  static uniform_int_distribution<> randdouble(from, to);
  return randdouble(gen);
}

string GetRandomString(int length = 5) {
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
