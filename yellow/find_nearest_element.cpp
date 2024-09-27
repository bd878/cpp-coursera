#include <set>
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;

set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border) {
  if (numbers.empty()) {
    return numbers.end();
  }

  auto lower = numbers.lower_bound(border);
  if (lower == numbers.begin()) {
    return lower;
  }

  if (lower == numbers.end()) {
    return prev(lower);
  }

  if ((border - *prev(lower)) <= (*lower - border)) {
    return prev(lower);
  }

  return lower;
}
