#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "merge_sort.h"

using namespace std;

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5, 9, 1, 2};
  MergeSort3(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
