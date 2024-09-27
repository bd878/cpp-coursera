#include "test_runner.h"

#include <algorithm>
#include <memory>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
    shared_ptr<T> object = nullptr;

    if (deallocated.size() > 0) {
      object = *deallocated.begin();
      deallocated.erase(deallocated.begin());
    } else {
      object = make_shared<T>();
    }

    allocated.insert(object);

    return object.get();
  }

  T* TryAllocate() {
    shared_ptr<T> object = nullptr;

    if (deallocated.size() > 0) {
      object = *deallocated.begin();
      deallocated.erase(deallocated.begin());
      allocated.insert(object);
    }

    return object.get();
  }

  void Deallocate(T* object) {
    auto it = find_if(allocated.begin(), allocated.end(), [&object](const auto& ptr){
      return ptr.get() == object;
    });

    if (it == allocated.end()) {
      throw invalid_argument("can not found an object");
    }

    deallocated.insert(*it);
    allocated.erase(it);
  }

private:
  set<shared_ptr<T>> allocated;
  set<shared_ptr<T>> deallocated;
};

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
