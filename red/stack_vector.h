#pragma once

#include <stdexcept>
#include <array>

using namespace std;

template <typename T, size_t N>
class StackVector {
private:
  array<T, N> data;
  size_t capacity = N;
  size_t size;
public:
  explicit StackVector(size_t a_size = 0) : size{a_size} {
    if (a_size > capacity) {
      throw invalid_argument(to_string(a_size) + " is above capacity " + to_string(N));
    }
  };

  T& operator[](size_t index) {
    if (index > size) {
      throw invalid_argument(to_string(index) + " is above size " + to_string(size));
    }
    return data[index];
  }
  const T& operator[](size_t index) const {
    if (index > size) {
      throw invalid_argument(to_string(index) + " is above size " + to_string(size));
    }
    return data[index];
  }

  typename array<T, N>::iterator begin() {
    return data.begin();
  }
  typename array<T, N>::iterator end() {
    return data.begin() + size;
  }
  typename array<T, N>::const_iterator begin() const {
    return data.begin();
  }
  typename array<T, N>::const_iterator end() const {
    return data.begin() + size;
  }

  size_t Size() const {
    return size;
  }
  size_t Capacity() const {
    return capacity;
  }

  void PushBack(const T& value) {
    if (size == capacity) {
      throw overflow_error("StackVector is full");
    }
    data[size] = value;
    size += 1;
  }
  T PopBack() {
    if (size == 0) {
      throw underflow_error("StackVector is empty");
    }
    return data[--size];
  }
};

