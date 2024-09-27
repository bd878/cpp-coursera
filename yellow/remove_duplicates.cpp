#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
void RemoveDuplicates(vector<T>& elements) {
  sort(elements.begin(), elements.end());
  auto new_end_it = unique(elements.begin(), elements.end());
  elements.erase(new_end_it, elements.end());
}
