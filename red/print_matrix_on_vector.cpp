#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };

  auto first = begin(*matrix.begin());
  auto last = end(*prev(matrix.end()));

  // prints rubbish
  copy(first, last, ostream_iterator<int>(cout, " "));
  cout << '\n';

  return 0;
}