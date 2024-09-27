#include <set>
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
struct PriorityItem {
  T value;
  int priority = 0;

  friend bool operator==(const PriorityItem& lhs, const PriorityItem& rhs) {
    return lhs.value == rhs.value;
  }
  friend bool operator<(const PriorityItem& lhs, const PriorityItem& rhs) {
    return lhs.value < rhs.value;
  }
  friend ostream& operator<<(ostream& out, const PriorityItem& other) {
    out << other.value;
    return out;
  }
};

template <typename ForwardIt>
void PrintSet(ForwardIt first, ForwardIt last) {
  copy(first, last, ostream_iterator<typename ForwardIt::value_type>(cout, " "));
  cout << '\n';
}

int main() {
  set<PriorityItem<int>> numbers{{5}, {4}};

  cout << "Before: ";
  PrintSet(numbers.begin(), numbers.end());

  auto item_it = numbers.find({4});
  auto hint = next(item_it);

  PriorityItem<int> item(move(*item_it));
  item.value = 10;
  numbers.erase(item_it);
  numbers.insert(hint, item);

  cout << "After: ";
  PrintSet(numbers.begin(), numbers.end());

  return 0;
}