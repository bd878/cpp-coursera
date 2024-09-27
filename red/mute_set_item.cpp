#include <set>
#include <utility>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

struct Item {
  int value = 0;
  Item(int num) : value(num) {}
  friend bool operator<(const Item& lhs, const Item& rhs) {
    return lhs.value < rhs.value;
  }
  friend ostream& operator<<(ostream& out, const Item& item) {
    out << item.value << ' ';
    return out;
  }
};

template <typename ForwardIt>
void PrintSet(ForwardIt first, ForwardIt last) {
  copy(first, last, ostream_iterator<typename ForwardIt::value_type>(cout));
  cout << '\n';
}

int main() {
  set<Item> items;
  items.insert({5});
  items.insert({4});
  cout << "Before mutation: ";
  PrintSet(items.begin(), items.end());
  cout << "After mutation: ";
  PrintSet(items.begin(), items.end());

  return 0;
}