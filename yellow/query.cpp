#include "query.h"

istream& operator >> (istream& is, Query& q) {
  q = Query();

  string operation_code;
  is >> operation_code;
  if (operation_code == "NEW_BUS") {
    q.type = QueryType::NewBus;
    is >> q.bus;
    int stop_count;
    is >> stop_count;

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