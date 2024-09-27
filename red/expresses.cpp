#include <fstream>
#include <iostream>

#include "profile.h"
#include "slow_express.h"

using namespace std;

int main() {
  RouteManager routes;

  ifstream fin("add_expresses.txt");
  int query_count;
  fin >> query_count;
  {
    vector<pair<long int, long int>> start_finish;
    start_finish.reserve(10e5);

    for (int i = 0; i < query_count; ++i) {
      long int start, finish;
      fin >> start >> finish;
      start_finish.push_back({ start, finish });
    }

    LOG_DURATION("AddRoute");
    for (const auto& [start, finish] : start_finish) {
      routes.AddRoute(start, finish);
    }
  }

  // ifstream fin2("go_expresses.txt");
  // ofstream fout2("express_routes.txt");
  // int nearest_count;
  // fin2 >> nearest_count;
  // {
  //   vector<pair<long int, long int>> start_finish;
  //   start_finish.reserve(10e5);

  //   for (int i = 0; i < nearest_count; ++i) {
  //     long int start, finish;
  //     fin2 >> start >> finish;
  //     start_finish.push_back({ start, finish });
  //   }

  //   LOG_DURATION("FindNearestFinish");
  //   for (const auto& [start, finish] : start_finish) {
  //     fout2 << routes.FindNearestFinish(start, finish) << '\n';
  //   }
  // }

  return 0;
}