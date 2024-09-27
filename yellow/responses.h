#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct BusesForStopResponse {
  string stop;
  vector<string> buses;
};

struct StopsForBusResponse {
  string bus;
  vector<pair<string, vector<string>>> stops;
};

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);
ostream& operator << (ostream& os, const StopsForBusResponse& r);
ostream& operator << (ostream& os, const AllBusesResponse& r);

