#include "test_runner.h"

#include <cstddef>  // нужно для nullptr_t
#include <utility>

using namespace std;

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr {
private:
  T* data;
public:
  UniquePtr() { data = new T(); }
  UniquePtr(T * ptr) { data = ptr; }
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr(UniquePtr&& other) { data = move(other.data); }
  UniquePtr& operator = (const UniquePtr&) = delete;
  UniquePtr& operator = (nullptr_t t) { delete data; data = t; }
  UniquePtr& operator = (UniquePtr&& other) { delete data; data = move(other.data); }
  ~UniquePtr() { delete data; }

  T& operator * () const { return *data; }

  T * operator -> () const { return data; }

  T * Release() { T* data_copy = data; data = nullptr; return data_copy; };

  void Reset(T * ptr) { delete data; data = ptr; }

  void Swap(UniquePtr& other) {
    T* data_transfer = data;
    data = other.data;
    other.data = data_transfer;
  }

  T * Get() const { return data; }
};


struct Item {
  static int counter;
  int value;
  Item(int v = 0): value(v) {
    ++counter;
  }
  Item(const Item& other): value(other.value) {
    ++counter;
  }
  ~Item() {
    --counter;
  }
};

int Item::counter = 0;


void TestLifetime() {
  Item::counter = 0;
  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    ptr.Reset(new Item);
    ASSERT_EQUAL(Item::counter, 1);
  }
  ASSERT_EQUAL(Item::counter, 0);

  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    auto rawPtr = ptr.Release();
    ASSERT_EQUAL(Item::counter, 1);

    delete rawPtr;
    ASSERT_EQUAL(Item::counter, 0);
  }
  ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters() {
  UniquePtr<Item> ptr(new Item(42));
  ASSERT_EQUAL(ptr.Get()->value, 42);
  ASSERT_EQUAL((*ptr).value, 42);
  ASSERT_EQUAL(ptr->value, 42);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLifetime);
  RUN_TEST(tr, TestGetters);
}
