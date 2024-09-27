#include <iostream>
#include <fstream>
#include <map>
#include <set>

using namespace std;

class BusRoutes {
private:
  map<set<string>, int> routes;
public:
  void addRoute(const set<string>&);
};

void BusRoutes::addRoute(const set<string>& stops) {
  if (routes.find(stops) != routes.end()) {
    cout << "Already exists for " << routes.at(stops) << endl;
  } else {
    int size = routes.size();
    routes[stops] = size + 1;
    cout << "New bus " << size + 1 << endl;
  }
}

int main() {
  fstream fin;
  fin.open("busroutes.txt");
  if (!fin.is_open()) {
    exit(EXIT_FAILURE);
    return 1;
  }

  BusRoutes routes;

  int n;
  fin >> n;
  for (int i = 0; i < n; ++i) {
    int stop_count;
    fin >> stop_count;
    set<string> stops;
    for (int j = 0; j < stop_count; ++j) {
      string stop;
      fin >> stop;
      stops.insert(stop);
    }
    routes.addRoute(stops);
  }

  return 0;
}