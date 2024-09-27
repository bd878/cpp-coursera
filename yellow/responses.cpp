#include "responses.h"

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
