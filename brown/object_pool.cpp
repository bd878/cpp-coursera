#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate();
  T* TryAllocate();

  void Deallocate(T* object);

  ~ObjectPool();

private:
  queue<T*> free;
  set<T*> allocated;
};

template <typename T>
T* ObjectPool<T>::Allocate() {
  if (free.empty()) {
    free.push(new T);
  }
  T* ret = free.front();
  free.pop();
  allocated.insert(ret);
  return ret;
}

template <typename T>
T* ObjectPool<T>::TryAllocate() {
  if (free.empty()) {
    return nullptr;
  }
  return Allocate();
}

template <typename T>
void ObjectPool<T>::Deallocate(T* object) {
  auto it = allocated.find(object);
  if (it == allocated.end()) {
    throw invalid_argument("");
  }
  allocated.erase(it);
  free.push(object);
}

template <typename T>
ObjectPool<T>::~ObjectPool() {
  while (!free.empty()) {
    T* ret = free.front();
    free.pop();
    delete ret;
  }

  for (T* item : allocated) {
    delete item;
  }
}

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
