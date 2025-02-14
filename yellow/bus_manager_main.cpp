#include <fstream>

#include "bus_manager.h"
#include "query.h"

using namespace std;

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
