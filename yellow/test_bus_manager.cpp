#include <sstream>
#include <iterator>
#include <algorithm>

#include "bus_manager.h"
#include "query.h"
#include "test_runner.h"

using namespace std;

void ReadsNewBus() {
  for (int i = 10; i--;) {
    string str{"NEW_BUS "};

    string busNumber{GetRandomString(5)};
    str += busNumber + " ";

    int stopsCount = GetRandomInt(1, 10);
    str += to_string(stopsCount);
    vector<string> stops;

    for (size_t j = stops.size(); j--;) {
      string stop{GetRandomString(10)};
      stops.push_back(stop);
      str += " " + stop;
    }

    Query q;
    stringstream ss{str};
    ss >> q;

    Assert(q.type == QueryType::NewBus, "Type is NewBus");
    AssertEqual(q.bus, busNumber, "Bus number is correct");
    AssertEqual(q.stops, stops, "Stops and order are correct");
  }
}

void ReadsBusesForStop() {
  for (int i = 10; i--;) {
    string request{"BUSES_FOR_STOP "};
    string stop{GetRandomString(5)};

    request += stop;

    Query q;
    stringstream ss{request};
    ss >> q;

    Assert(q.type == QueryType::BusesForStop, "Type is BusesForStop");
    AssertEqual(q.stop, stop, "Stop is correct");
  }
}

void ReadsStopBuses() {
  for (int i = 10; i--;) {
    string request{"STOPS_FOR_BUS "};
    string bus{GetRandomString(5)};

    request += bus;

    Query q;
    stringstream ss{request};
    ss >> q;

    Assert(q.type == QueryType::StopsForBus, "Type is StopsForBus");
    AssertEqual(q.bus, bus, "Bus is correct");
  }
}

void ReadsAllBuses() {
  stringstream ss{"ALL_BUSES"};
  Query q;
  ss >> q;
  Assert(q.type == QueryType::AllBuses, "Type is AllBuses");
}

void ReadsQuery() {
  TestRunner runner;

  runner.RunTest(ReadsNewBus, "ReadsNewBus");
  runner.RunTest(ReadsBusesForStop, "ReadsBusesForStop");
  runner.RunTest(ReadsStopBuses, "ReadsStopBuses");
  runner.RunTest(ReadsAllBuses, "ReadsAllBuses");
}

void AddsBus() {

}

void ManagesBusesAndStops() {
  TestRunner runner;

  runner.RunTest(AddsBus, "AddsBus");
}

void ParsesBusesForStopResponse() {
  for (int i = 10; i--; ) {
    string stop = GetRandomString(10);
    vector<string> buses{5};
    generate(begin(buses), end(buses), []{
      return GetRandomString(10);
    });

    BusesForStopResponse response = {stop, buses};

    ostringstream ss;
    ss << response;

    stringstream ss_buses;
    copy(begin(buses), end(buses), ostream_iterator<string>(ss_buses, " "));

    AssertEqual(ss.str(), ss_buses.str(), "Returns buses correctly");
  }
}

void ParsesStopsForBusResponse() {
  string bus{"5"};
  vector<pair<string, vector<string>>> stopsToBuses{
    {"stop1", {"1", "2", "3"}},
    {"stop2", {}},
    {"stop3", {"5"}}
  };
  StopsForBusResponse response{bus, stopsToBuses};

  ostringstream ss;
  ss << response;

  ostringstream ss_stops;
  transform(begin(stopsToBuses), end(stopsToBuses), ostream_iterator<string>(ss_stops, "\n"), [](const auto& stops) {
    ostringstream ss_buses;
    if (stops.second.size() == 0) {
      ss_buses << "no interchange";
    } else {
      copy(begin(stops.second), end(stops.second), ostream_iterator<string>(ss_buses, " "));
    }

    return "Stop " + stops.first + ": " + ss_buses.str();
  });

  AssertEqual(ss.str(), ss_stops.str(), "Parses stops to buses");
}

void ParsesStopsForEmptyBusResponse() {
  vector<pair<string, vector<string>>> stops{
    {"stop1", {"1", "2", "3k"}},
    {"stop2", {"5", "1", "4"}}
  };
  StopsForBusResponse response{"", stops};

  ostringstream ss;
  ss << response;
  AssertEqual(ss.str(), "No bus", "Returns No bus for empty bus and stops");
}

void ReturnsNoStopForEmptyStop() {
  BusesForStopResponse response;

  ostringstream ss;
  ss << response;
  AssertEqual(ss.str(), "No stop", "Returns No stop for empty stop");

  response.buses = {GetRandomString(3), GetRandomString(3), GetRandomString(3)};
  ss.str("");
  ss << response;
  AssertEqual(ss.str(), "No stop", "Returns No stop for empty stop and some buses");
}

void ParsesResponses() {
  TestRunner runner;

  runner.RunTest(ParsesBusesForStopResponse, "ParsesBusesForStopResponse");
  runner.RunTest(ReturnsNoStopForEmptyStop, "ReturnsNoStopForEmptyStop");
  runner.RunTest(ParsesStopsForBusResponse, "ParsesStopsForBusResponse");
  runner.RunTest(ParsesStopsForEmptyBusResponse, "ParsesStopsForEmptyBusResponse");
}

int main() {
  TestRunner runner;

  runner.RunTest(ReadsQuery, "ReadsQuery");
  runner.RunTest(ParsesResponses, "ParsesResponses");
  runner.RunTest(ManagesBusesAndStops, "ManagesBusesAndStops");

  return 0;
}
