#include <iostream>
#include <map>
#include <set>
#include <random>
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

void TestRootCount() {
  mt19937 gen;
  uniform_real_distribution<> unif(-10, 10);
  for (auto i = 0; i < 100; ++i) {
    const auto a = unif(gen);
    const auto b = unif(gen);
    const auto c = unif(gen);

    const auto count = GetDistinctRealRootCount(a, b, c);
    Assert(count >= 0 && count <= 2, "Has only 0, 1 or 2 real roots");
  }
}

void TwoRoots() {
  AssertEqual(GetDistinctRealRootCount(1, -2, -3), 2, "count(x^2 - 2x - 3 = 0) == 2");
  AssertEqual(GetDistinctRealRootCount(1, -8, 12), 2, "count(x^2 - 8x + 12 = 0) == 2");
}

void LinearEquation() {
  AssertEqual(GetDistinctRealRootCount(0, 8, -16), 1, "count(8x - 16 = 0) == 1");
  AssertEqual(GetDistinctRealRootCount(0, 8, 16), 1, "count(8x + 16 = 0) == 1");
  AssertEqual(GetDistinctRealRootCount(0, 5, 12), 1, "count(5x + 12 = 0) == 1");
  AssertEqual(GetDistinctRealRootCount(0, 1, 1), 1, "count(x + 1 = 0) == 1");
}

void ConstEquation() {
  AssertEqual(GetDistinctRealRootCount(0, 0, 10), 0, "count(10 = 0) == 0");
  AssertEqual(GetDistinctRealRootCount(0, 0, -1), 0, "count(-1 = 0) == 0");
  AssertEqual(GetDistinctRealRootCount(0, 0, 2.5), 0, "count(2.5 = 0) == 0");
}

void OneRoot() {
  AssertEqual(GetDistinctRealRootCount(1, -6, 9), 1, "count(x^2 - 6x + 6 = 0) == 1");
}

void NoRoots() {
  AssertEqual(GetDistinctRealRootCount(5, 3, 7), 0, "count(5x^2 + 3x + 7 = 0) == 0");
  AssertEqual(GetDistinctRealRootCount(5, 0, 30), 0, "count(5x^2 + 30 = 0) == 0");
}

int main() {
  TestRunner runner;

  runner.RunTest(TestRootCount, "TestRootCount");
  runner.RunTest(TwoRoots, "TwoRoots");
  runner.RunTest(ConstEquation, "ConstEquation");
  runner.RunTest(LinearEquation, "LinearEquation");
  runner.RunTest(OneRoot, "OneRoot");
  runner.RunTest(NoRoots, "NoRoots");

  return 0;
}
