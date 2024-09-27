#include <iostream>
#include <string>
#include <iterator>

#include "test_runner.h"
#include "remove_duplicates.h"

using namespace std;

void RemovesNumDuplicates() {
  vector<int> v_int{2, 2, 2, 2, 2, 2};
  RemoveDuplicates(v_int);
  AssertEqual(v_int.size(), 1, "Remove 2");

  for (int i = 10; i--; ) {
    vector<double> v(10);
    generate(begin(v), end(v), []{
      return GetRandomDouble(-100.0, 100.0);
    });
    set<double> v_s(begin(v), end(v));

    RemoveDuplicates<double>(v);

    AssertEqual(v.size(), v_s.size(), "Removes num duplicates");
  }
}

void RemovesStringDuplicates() {
  vector<string> v{"aaa", "aaa", "aaa", "b"};
  set<string> v_s(begin(v), end(v));

  RemoveDuplicates<string>(v);
  AssertEqual(v.size(), v_s.size(), "Removes strings");
}

void EmptyVector() {
  vector<string> v;
  RemoveDuplicates(v);
  AssertEqual(v.size(), v.size(), "Keeps empty vector still");
}

int main() {
  TestRunner runner;

  runner.RunTest(RemovesNumDuplicates, "RemovesNumDuplicates");
  runner.RunTest(RemovesStringDuplicates, "RemovesStringDuplicates");
  runner.RunTest(EmptyVector, "EmptyVector");
  return 0;
}