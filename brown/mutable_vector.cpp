#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename T>
class MutableVector {
private:
  vector<T> v;

  template <typename U>
  struct LValue {
    vector<U>& cont;
    size_t idx;

    void operator =(U u) {
      if (idx > cont.size()) {
        cont.resize(idx);
      }
      cont[idx] = move(u);
    }

    friend ostream& operator<<(ostream& out, const LValue& lv) {
      out << lv.cont[lv.idx];
      return out;
    }
  };
public:
  MutableVector(vector<T> values) : v(move(values)) {}

  T operator[](size_t idx) const {
    return idx > v.size() ? 0 : v[idx];
  }

  LValue<T> operator[](size_t idx) {
    return {v, idx};
  }
};

int main() {
  MutableVector<int> mv({1, 2, 3, 4, 5});
  cout << mv[4] << '\n';
  mv[4] = 2;
  cout << mv[4] << '\n';
  return 0;
}