#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    char prefix);

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const string& prefix);

int main() {
  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
  
  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;
  
  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;
  
  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;
  
  return 0;
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const string& prefix) {
  auto lower_it = lower_bound(range_begin, range_end, prefix, [](const auto& item, const string& p){
    size_t count = min(item.length(), p.length());
    return lexicographical_compare(item.begin(), item.begin() + count, p.begin(), p.begin() + count);
  });
  auto upper_it = upper_bound(range_begin, range_end, prefix, [](const string& p, const auto& item){
    size_t count = min(item.length(), p.length());
    return lexicographical_compare(p.begin(), p.begin() + count, item.begin(), item.begin() + count);
  });
  return {lower_it, upper_it};
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    char prefix) {
  auto lower_it = lower_bound(range_begin, range_end, prefix, [](const auto& item, char p){
    return item[0] < p;
  });
  auto upper_it = upper_bound(range_begin, range_end, prefix, [](char p, const auto& item){
    return p < item[0];
  });
  return {lower_it, upper_it};
}
