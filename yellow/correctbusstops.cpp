#include <string>
#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  q = Query();

  string operation_code;
  is >> operation_code;
  if (operation_code == "NEW_BUS") {
    q.type = QueryType::NewBus;
    is >> q.bus;
    int stop_count;
    is >> stop_count;
    q.stops.resize(stop_count);
    for (string& stop : q.stops) {
      is >> stop;
    }
  }

  if (operation_code == "BUSES_FOR_STOP") {
    q.type = QueryType::BusesForStop;
    is >> q.stop;    
  }

  if (operation_code == "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  }

  if (operation_code == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }

  return is;
}

struct BusesForStopResponse {
  string stop;
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.stop.empty()) {
    os << "No stop";
  } else {
    for (const string& bus : r.buses) {
      os << bus << " ";
    }
  }
  return os;
}

struct StopsForBusResponse {
  string bus;
  vector<pair<string, vector<string>>> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.bus.empty()) {
    os << "No bus";
  } else {
    for (const auto& [stop, interchanges] : r.stops) {
      os << "Stop " << stop << ": ";
      if (interchanges.empty()) {
        os << "no interchange";
      } else {
        for (const string& other_bus : interchanges) {
          os << other_bus << " ";
        }
      }
      os << endl;
    }
  }
  return os;
}

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.buses_to_stops.empty()) {
    os << "No buses";
  } else {
    for (const auto& [bus, stops] : r.buses_to_stops) {
      os << "Bus " << bus << ": ";
      for (const string& stop : stops) {
        os << stop << " ";
      }
      os << endl;
    }
  }
  return os;
}

class BusManager {
private:
  map<string, vector<string>> stops_to_buses;
  map<string, vector<string>> buses_to_stops;
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    for (const string& stop : stops) {
      stops_to_buses[stop].push_back(bus);
      buses_to_stops[bus].push_back(stop);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    BusesForStopResponse response;
    if (stops_to_buses.count(stop)) {
      response.stop = stop;
      response.buses = stops_to_buses.at(stop);
    }

    return response;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
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

  AllBusesResponse GetAllBuses() const {
    return {buses_to_stops};
  }
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  fstream fin("buses.txt");

  int query_count;
  Query q;

  fin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    fin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
