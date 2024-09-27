#include <cstdlib>
#include <iterator>
#include <utility>
#include <algorithm>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;

  explicit SimpleVector(size_t size) : size(size), capacity(size) {
    data = new T[size];
  };

  SimpleVector(const SimpleVector& v) {
    data = new T[v.capacity];
    std::copy(v.begin(), v.end(), begin());
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
      std::copy(v.begin(), v.end(), begin());
      size = v.size;
    } else {
      SimpleVector<T> tmp(v);
      std::swap(tmp.data, data);
      std::swap(tmp.size, size);
      std::swap(tmp.capacity, capacity);
    }
  }

  size_t Size() const {
    return size;
  }

  size_t Capacity() const {
    return capacity;
  }

  void PushBack(const T& value) {
    ExtendIfNeeded();
    data[size++] = value;
  }

  void PushBack(T&& value) {
    ExtendIfNeeded();
    data[size++] = std::move(value);
  }

private:
  void ExtendIfNeeded() {
    if (size >= capacity) {
      if (capacity == 0) {
        capacity = 1;
      }

      capacity *= 2;
      T* newData = new T[capacity];

      std::move(begin(), end(), newData);
      delete[] data;
      data = newData;
    }
  }

  T* data = nullptr;
  size_t size = 0;
  size_t capacity = 0;
};
