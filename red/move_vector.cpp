#include <utility>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename ForwardIt>
void PrintVector(ForwardIt, ForwardIt);

template <typename RandomIt>
void SortVector(RandomIt first, RandomIt last) {
  cout << "Create source" << '\n';
  vector<typename RandomIt::value_type> source(make_move_iterator(first), make_move_iterator(last));
  cout << "sort func" << '\n';
  sort(source.begin(), source.end());
  cout << "move loop" << '\n';
  for (size_t i = 0; i < distance(first, last); ++i) {
    auto source_it = source.begin() + i;
    auto arg_it = first + i;
    swap(*source_it, *arg_it);
  }
  cout << "source after move: ";
  PrintVector(source.begin(), source.end());
}

template <typename ForwardIt>
void PrintVector(ForwardIt first, ForwardIt last) {
  for (auto it = first; it != last; ++it) {
    cout << *it << ' ';
  }
  cout << endl;
}

struct NoncopyableInt {
  int value;

  NoncopyableInt(int value) : value(value) {
    cout << "Default " << value << '\n';
  }

  NoncopyableInt(const NoncopyableInt& num) = delete;
  NoncopyableInt& operator=(const NoncopyableInt& num) = delete;
  NoncopyableInt(NoncopyableInt&& num) {
    cout << "Move " << num.value << '\n';
    swap(num.value, value);
  }
  NoncopyableInt& operator=(NoncopyableInt&& num) {
    cout << "Move operator= " << num.value << '\n';
    swap(num.value, value);
    return *this;
  }

  friend bool operator<(const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
    return lhs.value < rhs.value;
  }
  friend bool operator==(const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
    return lhs.value == rhs.value;
  }
  friend ostream& operator<<(ostream& out, const NoncopyableInt& other) {
    out << other.value;
    return out;
  }
};

int main() {
  vector<NoncopyableInt> numbers;
  numbers.push_back({5});
  numbers.push_back({4});

  cout << "Before: ";
  PrintVector(numbers.begin(), numbers.end());

  cout << "Sort" << '\n';
  SortVector(begin(numbers), end(numbers));

  cout << "After: ";
  PrintVector(numbers.begin(), numbers.end());

  return 0;
}
