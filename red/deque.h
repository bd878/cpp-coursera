#include <vector>
#include <sstream>
#include <exception>
#include <iterator>
#include <iostream>

using namespace std;

template <typename T>
class Deque {
private:
  vector<T> front;
  vector<T> back;

  typename vector<T>::iterator getIteratorByIndex(size_t index) {
    if (index < front.size()) {
      return prev(prev(front.end()), index);
    }

    return next(back.begin(), index - front.size());
  }

  void isInRange(size_t index) {
    if (index >= Size() || index < 0) {
      ostringstream os;
      os << index << " is out of range";
      throw out_of_range(os.str());
    }
  }
public:
  Deque() = default;

  bool Empty() const {
    return front.empty() || back.empty();
  }

  size_t Size() const {
    return front.size() + back.size();
  }

  T& operator[](size_t index) {
    return (*getIteratorByIndex(index));
  }

  const T& operator[](size_t index) const {
    return (*getIteratorByIndex(index));
  }

  T& At(size_t index) {
    isInRange(index);
    return (*getIteratorByIndex(index));
  }

  const T& At(size_t index) const {
    isInRange(index);
    return (*getIteratorByIndex(index));
  }

  T& Front() {
    return At(0);
  }

  const T& Front() const {
    return At(0);
  }

  T& Back() {
    return At(Size() - 1);
  }

  const T& Back() const {
    return At(Size() - 1);
  }

  void PushFront(const T& value) {
    front.push_back(value);
  }

  void PushBack(const T& value) {
    back.push_back(value);
  }
};
