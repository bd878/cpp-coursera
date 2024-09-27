#pragma once

#include <vector>
#include <map>
#include <string>

#include "responses.h"

using namespace std;

class BusManager {
private:
  map<string, vector<string>> stops_to_buses;
  map<string, vector<string>> buses_to_stops;
public:
  void AddBus(const string& bus, const vector<string>& stops);

  BusesForStopResponse GetBusesForStop(const string& stop) const;
  StopsForBusResponse GetStopsForBus(const string& bus) const;
  AllBusesResponse GetAllBuses() const;
};
