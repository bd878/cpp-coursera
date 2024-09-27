#include <iterator>
#include <vector>
#include <iostream>

using namespace std;

template <typename Iterator>
struct IteratorRange {
  Iterator first, last;

  IteratorRange(Iterator f, Iterator l): first{f}, last{l} {};

  Iterator begin() {
    return first;
  }

  Iterator end() {
    return last;
  }

  size_t size() const {
    return distance(first, last);
  }
};

int main() {
  vector<int> s{1, 2, 3, 4, 5};
  IteratorRange r(s.begin(), s.end());

  size_t pages = 10;
  size_t total_items = r.size();
  int pages_count = (int)total_items / pages;
  int rest_items = total_items % pages;

  cout << "pages_count: " << pages_count << '\n';
  cout << "rest_items: " << rest_items << '\n';

  cout << endl;

  return 0;
}
