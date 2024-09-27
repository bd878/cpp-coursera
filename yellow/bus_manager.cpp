#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
  for (const string& stop : stops) {
    stops_to_buses[stop].push_back(bus);
    buses_to_stops[bus].push_back(stop);
  }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
  BusesForStopResponse response;
  if (stops_to_buses.count(stop)) {
    response.stop = stop;
    response.buses = stops_to_buses.at(stop);
  }

  return response;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
  StopsForBusResponse response;
  if (buses_to_stops.count(bus)) {
    response.bus = bus;
    for (const string& stop : buses_to_stops.at(bus)) {
      vector<string> interchanges;

      for (const string& other_bus : stops_to_buses.at(stop)) {
        if (other_bus != bus) {
          interchanges.push_back(other_bus);
        }
      }

      response.stops.push_back({stop, interchanges});
    }
  }

  return response;
}

AllBusesResponse BusManager::GetAllBuses() const {
  return {buses_to_stops};
}