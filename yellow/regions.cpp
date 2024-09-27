#include <iostream>
#include <vector>
#include <tuple>
#include <cstdint>
#include <map>

using namespace std;

bool operator<(const Region& lhs, const Region& rhs) {
  return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
    tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
  map<Region, int> regions_count;

  for (const auto& region : regions) {
    regions_count[region]++;
  }

  int max = 0;
  for (const auto& [region, count] : regions_count) {
    if (count > max) {
      max = count;
    }
  }

  return max;
}
