#include <iostream>
#include <iterator>

#include "sum_reverse_sort.h"
#include "test_runner.h"

void SumsDigits() {
  for (int i = 10; i--;) {
    int x = GetRandomInt(-100, 100);
    int y = GetRandomInt(-100, 100);

    AssertEqual(Sum(x, y), x + y, "Sums correctly");
  }
}

void ReversesString() {
  for (int i = 10; i--;) {
    string oddStr = GetRandomString(5);
    string evenStr = GetRandomString(10);
    string emptyStr = "   ";

    string reversedOdd = Reverse(oddStr);
    reverse(begin(oddStr), end(oddStr));
    AssertEqual(reversedOdd, oddStr, "Reverses correctly odd-length string");

    string reversedEven = Reverse(evenStr);
    reverse(begin(evenStr), end(evenStr));
    AssertEqual(reversedEven, evenStr, "Reverses correctly even-length string");

    string reversedEmpty = Reverse(emptyStr);
    reverse(begin(emptyStr), end(emptyStr));
    AssertEqual(reversedEmpty, emptyStr, "Reverses correctly empty string");
  }
}

void ReverseSingleString() {
  string testStr = "ab";
  string reversedTestStr = "ba";

  AssertEqual(Reverse(testStr), reversedTestStr, "Reversed correctly");
}

void SortsVector() {
  for (int i = 10; i--;) {
    vector<int> nums(10);
    vector<int> empty = {};

    generate_n(begin(nums), 10, []{
      return GetRandomInt(-1000, 1000);
    });

    vector<int> true_sorted_nums(nums);
    sort(begin(true_sorted_nums), end(true_sorted_nums));
    Sort(nums);
    AssertEqual(nums, true_sorted_nums, "Sorts random vector correctly");

    vector<int> true_sorted_empty = {};
    Sort(empty);
    AssertEqual(empty, true_sorted_empty, "Sorts empty vector correctly");
  }
}

void SortSingleVector() {
  vector<int> nums = {-5, 10, 16, 18, 100};
  vector<int> true_sorted_nums = nums;
  sort(begin(true_sorted_nums), end(true_sorted_nums));
  Sort(nums);
  AssertEqual(nums, true_sorted_nums, "Sorts single vector correctly");
}

void SortEmptyVector() {
  vector<int> empty = {};
  vector<int> empty2 = {};
  Sort(empty);
  AssertEqual(empty, empty2, "Sort empty vector");
}

int main() {
  TestRunner runner;

  runner.RunTest(SumsDigits, "SumsDigits");
  runner.RunTest(ReverseSingleString, "ReverseSingleString");
  runner.RunTest(ReversesString, "ReversesString");
  runner.RunTest(SortSingleVector, "SortSingleVector");
  runner.RunTest(SortEmptyVector, "SortEmptyVector");
  runner.RunTest(SortsVector, "SortsVector");

  return 0;
}