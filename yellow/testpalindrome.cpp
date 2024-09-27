#include <iostream>
#include <algorithm>
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

string GetRandomString(int length = 5) {
  string result(length, 0);

  static const string alphastring = "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    " ";

  static random_device rd;
  static mt19937 gen{rd()};
  static uniform_int_distribution<> charid(0, alphastring.size() - 1);

  auto generator = []() -> char {
    return alphastring.at(charid(gen));
  };

  generate_n(result.begin(), length, generator);
  return result;
}

bool IsPalindrom(const string& str) {
  // Вы можете вставлять сюда различные реализации функции,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
  return true;
}

void DefinesPalindrom() {
  Assert(IsPalindrom(""), "Empty string is is palindrom");

  for (int i = 10; i--;) {
    string first = GetRandomString();
    first += first;
    Assert(IsPalindrom(first), first + " is palindrom");

    string charstring = GetRandomString(1);
    Assert(IsPalindrom(charstring), charstring + " is palindrom");
  }
}

void DefinesPhrasePalindrom() {
  for (int i = 10; i--;) {
    string first = GetRandomString();
    string second = GetRandomString();
    string palindromPhrase = first + ' ' + second + ' ' + second + ' ' + first;
    Assert(IsPalindrom(palindromPhrase), palindromPhrase + " is phrase palindrom");
  }
}

void NotPalindrom() {
  for (int i = 10; i--;) {
    string first = GetRandomString(10);
    string phrase = GetRandomString(10) + ' ' + GetRandomString(7);
    AssertEqual(IsPalindrom(first), false, first + " is not a palindrom");
    AssertEqual(IsPalindrom(phrase), false, phrase + " is not a palindrom");
  }
}

int main() {
  TestRunner runner;
  
  runner.RunTest(DefinesPalindrom, "DefinesPalindrom");
  runner.RunTest(DefinesPhrasePalindrom, "DefinesPhrasePalindrom");
  runner.RunTest(NotPalindrom, "NotPalindrom");

  return 0;
}
