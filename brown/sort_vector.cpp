#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

using It = typename vector<int>::iterator;

void SortVector(It first, It last) {
  sort(first, last, [](int lhs, int rhs) {
    return lhs > rhs;
  });
}

int main() {
  vector<int> v{1, 2, 6, 4, 5};
  SortVector(begin(v), end(v));
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
  return 0;
}