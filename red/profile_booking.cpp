#include <iostream>
#include <fstream>

#include "profile.h"
#include "booking.h"
#include "gen_bookings.h"

using namespace std;

int main() {
  genBookings();

  ifstream fin("bookings.txt");
  ofstream fout("bookings_stats.txt");

  BookingManager manager;

  int query_count;
  fin >> query_count;

  {
    LOG_DURATION("BookingManager");
    for (int i = 0; i < query_count; i++) {
      string query;
      fin >> query;
      if (query == "BOOK") {
        long long time;
        string hotel_name;
        int client_id, room_count;

        fin >> time >> hotel_name
          >> client_id >> room_count;

        manager.Book(hotel_name, time, client_id, room_count);
      } else if (query == "CLIENTS") {
        string hotel_name;
        fin >> hotel_name;

        fout << manager.CountClients(hotel_name) << '\n';
      } else if (query == "ROOMS") {
        string hotel_name;
        fin >> hotel_name;

        fout << manager.CountRooms(hotel_name) << '\n';
      }
    }
  }

  return 0;
}