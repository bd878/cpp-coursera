#include <sstream>
#include <cmath>
#include <map>

#include "slow_express.h"
#include "test_runner.h"

using namespace std;

template <typename T>
ostream& PrintVector(ostream& os, const vector<T>& v) {
  for (auto& value : v) {
    os << value << ' ';
  }

  return os;
}

RouteManager InitRoutes(long int value, const vector<long int>& endpoints) {
  RouteManager routes;
  for (long int v : endpoints) {
    routes.AddRoute(value, v);
  }

  return routes;
}

void RunItems() {
  map<long int, vector<long int>> value_results{
    {0, {1, 2, 3, 4, 5}},
    {1000000000, {0, 1, 2}},
    {-1, {1, 2, 3}},
    {-1000000000, {1, 2, -100000000}}
  };

  for (const auto& [value, endpoints] : value_results) {
    stringstream ss;
    PrintVector(ss, endpoints);

    RouteManager routes = InitRoutes(value, endpoints);

    ostringstream result;
    PrintVector(result, routes.Destinations(value));

    ASSERT_EQUAL(ss.str(), result.str());

    for (long int v : endpoints) {
      long int nearest_finish = routes.FindNearestFinish(value, v);
      ASSERT_EQUAL(nearest_finish, 0);

      nearest_finish = routes.FindNearestFinish(v, value - 1);
      ASSERT_EQUAL(nearest_finish, 1);
    }
  }
}

int main() {
  TestRunner tr;

  RUN_TEST(tr, RunItems);

  return 0;
}