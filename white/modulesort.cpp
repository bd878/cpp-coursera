#include <iostream>
#include <iterator>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> numbers(n);
  for (int i = 0; i < n; ++i) {
    cin >> numbers[i];
  }
  sort(begin(numbers), end(numbers), [](int n1, int n2) {
    return abs(n1) < abs(n2);
  });
  copy(begin(numbers), end(numbers), ostream_iterator<int>{cout, " "});

  return 0;
}