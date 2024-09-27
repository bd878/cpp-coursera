#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>

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

int main() {
  vector<NoncopyableInt> numbers;
  vector<NoncopyableInt> moved;
  numbers.push_back({1});
  numbers.push_back({2});
  numbers.push_back({3});
  numbers.push_back({4});
  numbers.push_back({5});

  for_each(move_iterator(numbers.begin()), move_iterator(numbers.end()), ostream_iterator(cout, " "));

  for (auto it = numbers.begin(); it != numbers.end(); ++it) {
    moved.push_back(*it);
  }

  // val = 5;
  // cout << val << '\n';
  cout << "Numbers: " << '\n';
  PrintVector(numbers.begin(), numbers.end());
  cout << "Moved: " << '\n';
  PrintVector(moved.begin(), moved.end());

  return 0;
}