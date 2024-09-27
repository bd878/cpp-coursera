#pragma once

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "test_runner.h"
#include "profile.h"

using namespace std;

void genBookings(
  int max_client = 10e4,
  int max_queries = 10e3,
  long long from_time = 1,
  long long to_time = 10e12,
  int max_room = 10e3,
  int string_length = 12
) {
  LOG_DURATION("genBookings");

  ofstream fout("bookings.txt");

  auto requestQuery([]{
    switch (GetRandomInt(0, 2)) {
      case 0:
        return "BOOK";
      case 1:
        return "CLIENTS";
      case 2:
        return "ROOMS";
      default:
        return "BOOK";
    }
  });

  vector<string> hotels(100);
  auto getHotelName([&hotels, &string_length]{
    int hotel_id = GetRandomInt(1, 99);
    if (hotels[hotel_id].empty()) {
      string hotel_name(GetRandomString(string_length));
      hotels[hotel_id] = hotel_name;
      return hotel_name;
    } else {
      return hotels[hotel_id];
    }
  });

  long long time = from_time;
  int time_step = GetRandomInt(1, 1000);

  fout << max_queries << '\n';
  for (int i = 0; i < max_queries; i++) {
    string query(requestQuery());

    if (query == "BOOK") {
      time += time_step;
      string hotel_name(getHotelName());
      int client_id = GetRandomInt(1, max_client);
      int room_count = GetRandomInt(1, max_room);

      if (time > to_time) {
        throw overflow_error("time is out of range");
      }

      fout << "BOOK "
        << time << ' '
        << hotel_name << ' '
        << client_id << ' '
        << room_count << '\n';
    } else if (query == "CLIENTS") {
      fout << "CLIENTS "
        << getHotelName() << '\n';
    } else if (query == "ROOMS") {
      fout << "ROOMS "
        << getHotelName() << '\n';
    }
  }
}