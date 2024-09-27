#include "test_runner.h"
#include <iterator>
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  size_t size = distance(range_begin, range_end);

  if (size < 2) {
    return;
  }

  vector<typename RandomIt::value_type> first(
    make_move_iterator(range_begin),
    make_move_iterator(range_begin + size / 3)
  );

  vector<typename RandomIt::value_type> second(
    make_move_iterator(range_begin + size / 3),
    make_move_iterator(range_begin + (size / 3) * 2)
  );

  vector<typename RandomIt::value_type> third(
    make_move_iterator(range_begin + (size / 3) * 2),
    make_move_iterator(range_end)
  );

  MergeSort(first.begin(), first.end());
  MergeSort(second.begin(), second.end());
  MergeSort(third.begin(), third.end());

  vector<typename RandomIt::value_type> result;
  merge(
    first.begin(), first.end(),
    second.begin(), second.end(),
    back_inserter(result)
  );
  vector<typename RandomIt::value_type> source;
  merge(
    result.begin(), result.end(),
    third.begin(), third.end(),
    back_inserter(source)
  );

  for (size_t i = 0; i < size; ++i) {
    auto source_it = source.begin() + i;
    auto arg_it = range_begin + i;
    swap(*source_it, *arg_it);
  }
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
