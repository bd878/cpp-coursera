#include <iostream>
#include <cmath>
#include <unordered_map>
#include <iterator>
#include <deque>

using namespace std;

class BookingManager {
private:
  static const int DAY_SECONDS = 86400;
public:
  using Hotel = string;
  using ClientId = size_t;

  struct Booking {
    int64_t timestamp;
    string hotel;
    int client_id;
    int count;
  };

  void Book(int64_t timestamp, string hotel, int id, int count) {
    bookings.push_back({timestamp, hotel, id, count});
    rooms[hotel] += count;
    clients[hotel][id] += count;
    FitToDayInterval(timestamp);
  }

  int Rooms(const string& hotel_name) const {
    if (rooms.count(hotel_name) == 0) {
      return 0;
    }
    return rooms.at(hotel_name);
  }

  int Clients(const string& hotel_name) const {
    if (clients.count(hotel_name) == 0) {
      return 0;
    }
    return clients.at(hotel_name).size();
  }
private:
  deque<Booking> bookings;
  unordered_map<Hotel, int> rooms;
  unordered_map<Hotel, unordered_map<ClientId, int>> clients;

  void FitToDayInterval(int64_t timestamp) {
    auto it = bookings.begin();
    while (it != bookings.end() && abs(timestamp - it->timestamp) >= DAY_SECONDS) {
      rooms[it->hotel] -= it->count;
      clients[it->hotel][it->client_id] -= it->count;

      if (rooms[it->hotel] == 0) {
        rooms.erase(it->hotel);
      }

      if (clients[it->hotel][it->client_id] == 0) {
        clients[it->hotel].erase(it->client_id);
      }

      if (clients[it->hotel].size() == 0) {
        clients.erase(it->hotel);
      }

      ++it;
      bookings.pop_front();
    }
  }
};


int main() {
  BookingManager manager;

  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int count;
  cin >> count;

  for (int i = 0; i < count; ++i) {
    string query;
    cin >> query;

    if (query == "BOOK") {
      string hotel_name;
      int64_t timestamp;
      int client_id, room_count;

      cin >> timestamp >> hotel_name >> client_id >> room_count;
      manager.Book(timestamp, hotel_name, client_id, room_count);
    } else if (query == "CLIENTS") {
      string hotel_name;
      cin >> hotel_name;

      cout << manager.Clients(hotel_name) << '\n';
    } else if (query == "ROOMS") {
      string hotel_name;
      cin >> hotel_name;

      cout << manager.Rooms(hotel_name) << '\n';
    }
  }
}