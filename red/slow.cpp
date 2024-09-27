#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Routes {
private:
  vector<vector<vector<long int>>> routes;
public:
  Routes() {
    routes.resize(10e2);
    for (auto& route : routes) {
      route.reserve(10e5);
    }
  }

  const vector<long int>& operator[](long int index) const {
    int storage_index = (int)index / 10e5;
    int value_index = index - (storage_index * 10e5);

    return routes[storage_index][value_index];
  }

  vector<long int>& operator[](long int index) {
    int storage_index = (int)index / 10e5;
    int value_index = index - (storage_index * 10e5);

    return routes[storage_index][value_index];
  }
};

class RouteManager {
private:
  Routes negative_routes;
  Routes positive_routes;
public:
  void AddRoute(long int start, long int finish) {
    if (start >= 0) {
      positive_routes[start].push_back(finish);
    } else {
      negative_routes[abs(start)].push_back(finish);
    }

    if (finish >= 0) {
      positive_routes[finish].push_back(start);
    } else {
      negative_routes[abs(finish)].push_back(start);
    }
  }

  const vector<long int>& Destinations(long int value) const {
    if (value >= 0) {
      return positive_routes[value];
    } else {
      return negative_routes[abs(value)];
    }
  }

  long int FindNearestFinish(long int start, long int finish) const {
    long int result = abs(start - finish);

    const vector<long int>& reachable_stations = Destinations(start);
    if (reachable_stations.empty()) {
      return result;
    }

    return min(
      result,
      abs(finish - *min_element(
        reachable_stations.begin(), reachable_stations.end(),
        [finish](long int lhs, long int rhs) { return abs(lhs - finish) < abs(rhs - finish); }
      ))
    );
  }
};

int main() {
  RouteManager routes;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    long int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }

  return 0;
}
