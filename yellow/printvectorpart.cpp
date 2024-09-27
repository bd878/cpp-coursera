#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
  auto negative_it = find_if(begin(numbers), end(numbers), [](int num){ return num < 0; });
  for (auto it = negative_it; it != begin(numbers);) {
    cout << *(--it) << ' ';
  }
}
