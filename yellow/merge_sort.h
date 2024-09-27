#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);

template <typename RandomIt>
void MergeSort3(RandomIt range_begin, RandomIt range_end);

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  if (range_end - range_begin > 1) {
    vector<typename RandomIt::value_type> el(range_begin, range_end);
    auto middle_it = begin(el) + (end(el) - begin(el)) / 2;

    MergeSort(begin(el), middle_it);
    MergeSort(middle_it, end(el));

    merge(begin(el), middle_it, middle_it, end(el), range_begin);
  }
}

template <typename RandomIt>
void MergeSort3(RandomIt range_begin, RandomIt range_end) {
  if (range_end - range_begin > 1) {
    vector<typename RandomIt::value_type> el(range_begin, range_end);
    auto left_middle_it = begin(el) + (end(el) - begin(el)) / 3;
    auto right_middle_it = left_middle_it + (end(el) - begin(el)) / 3;

    MergeSort3(begin(el), left_middle_it);
    MergeSort3(left_middle_it, right_middle_it);
    MergeSort3(right_middle_it, end(el));

    vector<typename RandomIt::value_type> temp;
    merge(begin(el), left_middle_it, left_middle_it, right_middle_it, back_inserter(temp));
    merge(begin(temp), end(temp), right_middle_it, end(el), range_begin);
  }
}
