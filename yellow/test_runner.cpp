#include "test_runner.h"

TestRunner::~TestRunner() {
  if (fail_count > 0) {
    cerr << fail_count << " unit tests failed. Terminate" << endl;
    exit(1);
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

int GetRandomInt(int from, int to) {
  static random_device rd;
  static mt19937 gen{rd()};
  static uniform_int_distribution<> randint(from, to);
  return randint(gen);
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
