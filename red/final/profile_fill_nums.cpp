#include <future>
#include <vector>
#include <algorithm>

#include "paginator.h"
#include "profile.h"

using namespace std;

int GetRandomInt() {
  return 5;
}

int main() {
  const size_t NUMS_COUNT = 10e6;
  {
    LOG_DURATION("Sync fill");
    vector<int> nums(NUMS_COUNT);
    generate(nums.begin(), nums.end(), []{ return GetRandomInt(); });
  }
  {
    LOG_DURATION("Parallel fill");
    vector<int> nums(NUMS_COUNT);
    vector<future<void>> futures;
    for (auto page : Paginate(nums, NUMS_COUNT / 4)) {
      futures.push_back(async([page]{
        generate(page.begin(), page.end(), []{ return GetRandomInt(); });
      }));
    }
  }

  return 0;
}