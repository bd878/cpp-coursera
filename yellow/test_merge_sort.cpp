#include <iostream>
#include <string>
#include <algorithm>

#include "test_runner.h"
#include "merge_sort.h"

using namespace std;

void SortsNums() {
  vector<int> empty{0};
  vector<int> empty_copy(begin(empty), end(empty));
  MergeSort3(empty.begin(), empty.end());
  AssertEqual(empty, empty_copy, "Leaves empty vector");

  for (int i = 10; i--; ) {
    vector<int> v_i(100);
    generate(begin(v_i), end(v_i), []{ return GetRandomInt(-1000, 1000); });

    vector<int> sorted_v_i(v_i.begin(), v_i.end());
    sort(begin(sorted_v_i), end(sorted_v_i));

    vector<double> v_f(100);
    generate(begin(v_f), end(v_f), []{ return GetRandomDouble(-1000, 1000); });

    vector<double> sorted_v_f(v_f.begin(), v_f.end());
    sort(begin(sorted_v_f), end(sorted_v_f));

    MergeSort3(v_i.begin(), v_i.end());
    MergeSort3(v_f.begin(), v_f.end());

    AssertEqual(v_i, sorted_v_i, "Sorts ints");
    AssertEqual(v_f, sorted_v_f, "Sorts floats");
  }
}

void SortsStrings() {
  for (int i = 10; i--; ) {
    vector<string> v{100};
    generate(begin(v), end(v), []{ return GetRandomString(20); });

    vector<string> sortedv(begin(v), end(v));
    sort(begin(sortedv), end(sortedv));

    MergeSort3(v.begin(), v.end());

    AssertEqual(v, sortedv, "Sorts full strings correctly");
  }
}

int main() {
  TestRunner runner;

  runner.RunTest(SortsNums, "SortsNums");
  runner.RunTest(SortsStrings, "SortsStrings");

  return 0;
}