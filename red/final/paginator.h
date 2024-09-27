#pragma once

#include <algorithm>
#include <iterator>
#include <vector>

#include "iterator_range.h"

using namespace std;

template <typename Iterator>
class Paginator {
private:
  vector<IteratorRange<Iterator>> pages;
public:
  Paginator(Iterator start, Iterator finish, size_t page_size) {
    size_t total_items = distance(start, finish);
    int pages_count = (int)total_items / page_size;

    Iterator it = start;
    for (int i = 0; i < pages_count; i++, advance(it, page_size)) {
      pages.push_back({ it, next(it, page_size) });
    }

    if (it != finish) {
      pages.push_back({ it, finish });
    }
  };

  auto begin() const {
    return pages.begin();
  }

  auto end() const {
    return pages.end();
  }

  size_t size() const {
    return pages.size();
  }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(c.begin(), c.end(), page_size);
}