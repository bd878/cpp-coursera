#include <algorithm>

#include "sum_reverse_sort.h"

using namespace std;

int Sum(int x, int y) {
  return x + y;
}

string Reverse(string s) {
  for (size_t i = 0, j = s.size() - 1; i < j; ++i, --j) {
    char left = s[i];
    char right = s[j];
    s[i] = right;
    s[j] = left;
  }

  return s;
}

void Sort(vector<int>& nums) {
  sort(nums.begin(), nums.end());
}
