#include <iostream>
#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

using namespace std;

struct NoncopyableInt {
  int value;

  NoncopyableInt(int value) : value(value) {}

  NoncopyableInt(const NoncopyableInt&) = delete;
  NoncopyableInt& operator=(const NoncopyableInt&) = delete;

  NoncopyableInt(NoncopyableInt&&) = default;
  NoncopyableInt& operator=(NoncopyableInt&&) = default;
  friend ostream& operator<<(ostream& fout, const NoncopyableInt& i) {
    fout << i.value;
    return fout;
  }
};

template <typename It>
void PrintVector(It begin, It end) {

  for (It it = begin; it != end; ++it) {
    cout << *it << ' ';
  }

  cout << '\n';
}

template <typename RandomIt>
void IsValidCopy(RandomIt first, RandomIt last) {
  vector<typename RandomIt::value_type> pool{make_move_iterator(first), make_move_iterator(last)};
  // vector<typename RandomIt::value_type> pool(first, last); // should fail

  // pool.insert(
  //   pool.last(),
  //   move_iterator<RandomIt>(first),
  //   move_iterator<RandomIt>(last)
  // );

  for_each(make_move_iterator(first), make_move_iterator(last), back_inserter(pool));

  *prev(last) = move(pool[0]);

  cout << "Copied numbers: " << '\n';
  PrintVector(pool.begin(), pool.end());
}

int main() {
  vector<NoncopyableInt> numbers;
  numbers.push_back({1});
  numbers.push_back({2});

  cout << "Original numbers:" << '\n';
  PrintVector(numbers.begin(), numbers.end());

  IsValidCopy(numbers.begin(), numbers.end());
  cout << "Moved original: " << '\n';
  PrintVector(numbers.begin(), numbers.end());

  return 0;
}