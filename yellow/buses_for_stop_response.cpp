#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

#include "responses.h"
#include "test_runner.h"

using namespace std;

int main() {
  string stop = GetRandomString(10);
  cout << stop << endl;
  vector<string> buses{5};
  generate_n(buses.begin(), 5, [](){
    return GetRandomString(10);
  });

  BusesForStopResponse response = {stop, buses};

  cout << response << endl;

  ostringstream ss;
  ss << response;

  stringstream ss_buses;
  copy(begin(buses), end(buses), ostream_iterator<string>(ss_buses, " "));
  return 0;
}