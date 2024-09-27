#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
void RemoveDuplicates(vector<T>& elements) {
  auto new_end_it = end(elements);
  for (auto it = begin(elements); it != new_end_it; it++) {
    auto duplicate_it = find(next(it), new_end_it, *it);
    if (duplicate_it != new_end_it) {
      *duplicate_it = move(*prev(new_end_it));
      it--;
      new_end_it--;
    }
  }
  elements.erase(new_end_it, end(elements));
}
