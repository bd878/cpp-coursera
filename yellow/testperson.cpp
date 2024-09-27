#include <iostream>
#include <random>
#include <algorithm>
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

void GetsFullName() {
  Person emptyPerson;
  emptyPerson.ChangeFirstName(0, "");
  emptyPerson.ChangeLastName(0, "");
  AssertEqual(emptyPerson.GetFullName(0), "Incognito", "Empty first name and last name result Incognito");

  Person fullPerson;
  string firstName{getRandomString(10)};
  string lastName{getRandomString(10)};
  fullPerson.ChangeFirstName(800, firstName);
  fullPerson.ChangeLastName(800, lastName);
  AssertEqual(fullPerson.GetFullName(800), firstName + ' ' + lastName, "Full first and last name");
}

void IncognitoPerson() {
  Person person;
  AssertEqual(person.GetFullName(0), "Incognito", "Incognito");

  Person personWithFirstName;
  string firstName{getRandomString(10)};
  personWithFirstName.ChangeFirstName(1610, firstName);
  AssertEqual(personWithFirstName.GetFullName(1610), firstName + " with unknown last name", "Unknown last name");

  Person personWithLastName;
  string lastName{getRandomString(10)};
  personWithLastName.ChangeLastName(1610, lastName);
  AssertEqual(personWithLastName.GetFullName(1610), lastName + " with unknown first name", "Unknown first name");
}

void ChangesLastName() {
  Person person;
  for (int i = 100; i > 0; i -= 7) {
    string lastName{getRandomString(10)};
    person.ChangeLastName(500 - i, lastName);
    AssertEqual(person.GetFullName(500 - i), lastName + " with unknown first name");
  }
}

void ChangesFirstName() {
  Person person;
  for (int i = 100; i > 0; i -= 7) {
    string firstName{getRandomString(10)};
    person.ChangeFirstName(500 - i, firstName);
    AssertEqual(person.GetFullName(500 - i), firstName + " with unknown last name");
  }
}

void ChangesFullName() {
  Person person;
  for (int i = 100; i > 0; i -= 7) {
    string firstName{getRandomString(10)};
    string lastName{getRandomString(10)};
    person.ChangeFirstName(500 - i, firstName);
    person.ChangeLastName(500 - i, lastName);
    AssertEqual(person.GetFullName(500 - i), firstName + ' ' + lastName);
  }
}

int main() {
  TestRunner runner;

  runner.RunTest(GetsFullName, "GetsFullName");
  runner.RunTest(IncognitoPerson, "IncognitoPerson");
  runner.RunTest(ChangesFirstName, "ChangesFirstName");
  runner.RunTest(ChangesLastName, "ChangesLastName");
  runner.RunTest(ChangesFullName, "ChangesFullName");

  return 0;
}
