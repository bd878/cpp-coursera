#include <algorithm>

#include "deque.h"
#include "test_runner.h"

using namespace std;

vector<string> GetRandomVectorOfStrings(size_t count = 10) {
  vector<string> result(10);
  generate_n(result.begin(), count, []{ return GetRandomString(5); });
  return result;
}

void PushesElements() {
  Deque<string> d;

  vector<string> front = GetRandomVectorOfStrings();
  vector<string> back = GetRandomVectorOfStrings();

  for (const auto& value : front) {
    d.PushFront(value);
  }

  for (const auto& value : back) {
    d.PushBack(value);
  }

  reverse(front.begin(), front.end());

  ASSERT_EQUAL(d[0], front.front());
  ASSERT_EQUAL(d[d.Size() - 1], back.back());
}

int main() {
  TestRunner tr;

  RUN_TEST(tr, PushesElements);

  return 0;
}