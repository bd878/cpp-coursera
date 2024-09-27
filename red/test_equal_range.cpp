#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  vector<string> str{"efg", "cde", "ghi", "abc"};

  sort(str.begin(), str.end());
  const auto& [lower, upper] = equal_range(str.begin(), str.end(), "xyz");
  cout << "lower: " << (*prev(lower)) << '\n';
  cout << "upper: " << (*prev(upper)) << '\n';

  return 0;
}