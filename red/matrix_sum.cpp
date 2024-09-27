#include "test_runner.h"
#include <future>
#include <functional>
#include <cstdint>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

template <typename Iterator>
class IteratorRange {
private:
  Iterator first, last;
  size_t _size;
public:
  IteratorRange(Iterator f, Iterator l)
    : first{f}
    , last{l}
    , _size{distance(first, last)} {};

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

  size_t size() const {
    return _size;
  }
};

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

template <typename VectorMatrix>
int64_t SumSingleThread(const VectorMatrix& matrix) {
  int64_t result = 0;
  for (const auto& row : matrix) {
    for (auto item : row) {
      result += item;
    }
  }
  return result;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  vector<future<int64_t>> futures;
  for (auto page : Paginate(matrix, 2000)) {
    futures.push_back(async(SumSingleThread, ref(page)));
  }

  int64_t result = 0;
  for (auto& f : futures) {
    result += f.get();
  }

  return result;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
  return 0;
}
