#pragma once

#include <string>
#include <algorithm>
#include <numeric>
#include <memory>
#include <set>
#include <map>

using namespace std;

struct Booking {
  Booking(long long t, const string& name, int uid, int count): 
    timestamp(t), hotel_name(name), client_id(uid), room_count(count) {};

  Booking(): timestamp(0), hotel_name(""), client_id(0), room_count(0) {};

  long long timestamp;
  string hotel_name;
  int client_id;
  int room_count;
};

class BookingManager {
private:
  static const int SECONDS_IN_DAY = 86400;

  vector<shared_ptr<Booking>> bookings;
  map<string, pair<int, set<int>>> hotels;
  long long last;

  void UpdateHotels() {
    hotels.clear();

    for (auto it = bookings.rbegin(); it != bookings.rend(); ++it) {
      auto& booking = *it;

      if ((last - booking->timestamp) > SECONDS_IN_DAY) {
        break;
      }

      if (hotels.count(booking->hotel_name) == 0) {
        hotels[booking->hotel_name].first = 0;
      }

      hotels[booking->hotel_name].first += booking->room_count;
      hotels[booking->hotel_name].second.insert(booking->client_id);
    }
  }
public:
  BookingManager() : last(0) {};

  void Book(const string& hotel_name, long long time, int client_id, int room_count) {
    last = time;

    bookings.push_back(make_shared<Booking>(time, hotel_name, client_id, room_count));
    UpdateHotels();
  }

  int CountClients(const string& hotel_name) {
    if (hotels.count(hotel_name) == 0) {
      return 0;
    }

    return hotels.at(hotel_name).second.size();
  }

  int CountRooms(const string& hotel_name) {
    if (hotels.count(hotel_name) == 0) {
      return 0;
    }

    return hotels.at(hotel_name).first;
  }
};
