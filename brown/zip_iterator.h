#include <iostream>
#include <cstddef>
#include <vector>
#include <numeric>

template <typename T>
class zip_iterator {
  using it_type = typename std::vector<T>::iterator;
  it_type it1;
  it_type it2;

  explicit zip_iterator(it_type first, it_type second)
    : it1{first}, it2{second} {}

  zip_iterator& operator++() {
    ++it1;
    ++it2;
    return *this;
  }

  bool operator!=(const zip_iterator& o) const {
    return it1 != o.it1 && it2 != o.it2;
  }

  bool operator==(const zip_iterator& o) const {
    return !operator!=(o);
  }

  std::pair<double, double> operator*() const {
    return {it1, it2};
  }
};

namespace std {
template<typename T>
struct iterator_traits<zip_iterator<T>> {
  using iterator_category = std::forward_iterator_tag;
  using value_type = std::pair<T, T>;
  using difference_type = std::ptrdiff_t;
};
}