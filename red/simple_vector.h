#pragma once

#include <cstdlib>
#include <utility>
#include <algorithm>

using namespace std;

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector() : size(0), capacity(0), data(nullptr) {};

  explicit SimpleVector(size_t size) : size(size), capacity(size) {
    data = new T[size];
  };

  SimpleVector(const SimpleVector& v) {
    data = new T[v.capacity];
    copy(v.begin(), v.end(), begin());
    size = v.size;
    capacity = v.capacity;
  }

  ~SimpleVector() {
    delete[] data;
  }

  T& operator[](size_t index) {
    return data[index];
  }

  T* begin() {
    return data;
  }

  T* end() {
    return data + size;
  }

  const T* begin() const {
    return data;
  }

  const T* end() const {
    return data + size;
  }

  void operator=(const SimpleVector& v) {
    if (v.size <= capacity) {
      copy(v.begin(), v.end(), begin());
      size = v.size;
    } else {
      SimpleVector<T> tmp(v);
      swap(tmp.data, data);
      swap(tmp.size, size);
      swap(tmp.capacity, capacity);
    }
  }

  size_t Size() const {
    return size;
  }

  size_t Capacity() const {
    return capacity;
  }

  void PushBack(const T& value) {
    if (size >= capacity) {
      if (capacity == 0) {
        capacity = 1;
      }

      capacity *= 2;
      T* newData = new T[capacity];

      for (size_t i = 0; i < size; ++i) {
        newData[i] = data[i];
      }

      data = newData;
    }

    data[size++] = value;
  }

private:
  T* data;
  size_t size;
  size_t capacity;
};
