#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>

using namespace std;

class BusRoutes {
private:
  map<string, vector<string>> buses;
  vector<string> bus_order;
public:
  bool hasStop(const string&) const;
  bool hasBus(const string&) const;
  void addBus(const string&, vector<string>&);
  vector<string> getBusesForStop(const string&) const;
  void showBusesForStop(const string&) const;
  void showStopsForBus(const string&) const;
  void showRoutes() const;
};

bool BusRoutes::hasStop(const string& stop) const {
  for (const auto& [bus, bus_stops] : buses) {
    if (find(begin(bus_stops), end(bus_stops), stop) != end(bus_stops)) {
      return true;
    }
  }
  return false;
}

bool BusRoutes::hasBus(const string& bus) const {
  if (buses.find(bus) != buses.end()) {
    return true;
  }
  return false;
}

void BusRoutes::addBus(const string& bus, vector<string>& bus_stops) {
  bus_order.push_back(bus);

  for (const auto& stop : bus_stops) {
    buses[bus].push_back(stop);
  }
}

vector<string> BusRoutes::getBusesForStop(const string& stop) const {
  vector<string> buses_for_stop;

  if (hasStop(stop)) {
    for (const auto& bus : bus_order) {
      const auto& bus_stops = buses.at(bus);
      if (find(begin(bus_stops), end(bus_stops), stop) != end(bus_stops)) {
        buses_for_stop.push_back(bus);
      }
    }
  }

  return buses_for_stop;
}

void BusRoutes::showBusesForStop(const string& stop) const {
  if (!hasStop(stop)) {
    cout << "No stop" << endl;
  } else {
    vector<string> buses = getBusesForStop(stop);
    copy(begin(buses), end(buses), ostream_iterator<string>{cout, " "});
    cout << endl;
  }
}

void BusRoutes::showStopsForBus(const string& bus) const {
  if (!hasBus(bus)) {
    cout << "No bus" << endl;
  } else {
    for (const auto& stop : buses.at(bus)) {
      cout << "Stop " << stop << ": ";

      vector<string> stop_buses = getBusesForStop(stop);
      for (const auto& stop_bus : stop_buses) {
        if (stop_bus == bus) {
          if (stop_buses.size() == 1) {
            cout << "no interchange";
          }
        } else {
          cout << stop_bus << " ";
        }
      }

      cout << endl;
    }
  }
}

void BusRoutes::showRoutes() const {
  if (buses.size() == 0) {
    cout << "No buses" << endl;
  } else {
    for (const auto& [bus, bus_stops] : buses) {
      cout << "Bus " << bus << ": ";
      for (const auto& stop : bus_stops) {
        cout << stop << " ";
      }
      cout << endl;
    }
  }
}

int main() {
  fstream fin;
  fin.open("buses.txt");
  if (!fin.is_open()) {
    exit(EXIT_FAILURE);
    return 1;
  }

  BusRoutes routes;

  int n;
  fin >> n;
  for (int i = 0; i < n; ++i) {
    string command;
    fin >> command;
    if (command == "NEW_BUS") {
      string bus;
      int stop_count;
      vector<string> stops;

      fin >> bus;
      fin >> stop_count;

      stops.reserve(stop_count);
      for (int i = 0; i < stop_count; ++i) {
        string stop;
        fin >> stop;
        stops.push_back(stop);
      }

      routes.addBus(bus, stops);
    } else if (command == "BUSES_FOR_STOP") {
      string stop;
      fin >> stop;

      routes.showBusesForStop(stop);
    } else if (command == "STOPS_FOR_BUS") {
      string bus;
      fin >> bus;

      routes.showStopsForBus(bus);
    } else if (command == "ALL_BUSES") {
      routes.showRoutes();
    }
  }

  return 0;
}