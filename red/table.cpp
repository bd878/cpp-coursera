#include <vector>
#include <algorithm>

using namespace std;

// Реализуйте здесь шаблонный класс Table

template <typename T>
class Table {
private:
  vector<vector<T>> table;
public:
  Table(size_t rows, size_t columns) {
    Resize(rows, columns);
  }

  const vector<T>& operator[](size_t row) const {
    return table[row];
  }

  vector<T>& operator[](size_t row) {
    return table[row];
  }

  pair<size_t, size_t> Size() const {
    if (!table.empty() && !table[0].empty()) {
      return {table.size(), table[0].size()};
    }

    return {0, 0};
  }

  void Resize(size_t rows, size_t columns) {
    table.resize(rows);
    for (auto& column : table) {
      column.resize(columns);
    }
  }
};
