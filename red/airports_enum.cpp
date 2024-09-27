#include <iostream>
#include <tuple>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>
#include <list>
#include <array>

using namespace std;

template <typename TAirport>
class AirportCounter {
private:
  static const int COUNT = static_cast<uint32_t>(TAirport::Last_);
  array<pair<TAirport, size_t>, COUNT> airports;

  void Init() {
    for (size_t i = 0; i < airports.size(); ++i) {
      TAirport idx = static_cast<TAirport>(i);
      airports[i] = make_pair(idx, 0);
    }
  }
public:
  AirportCounter() {
    Init();
  };

  template <typename TIterator>
  AirportCounter(TIterator begin, TIterator end) {
    Init();

    for (TIterator it = begin; it != end; ++it) {
      Insert(*it);
    }
  }

  using Item = pair<TAirport, size_t>;
  using Items = array<Item, COUNT>;

  size_t Get(TAirport airport) const {
    return airports.at(static_cast<size_t>(airport)).second;
  }

  void Insert(TAirport airport) {
    airports[static_cast<size_t>(airport)].second += 1;
  }

  void EraseOne(TAirport airport) {
    airports[static_cast<size_t>(airport)].second -= 1;
  }

  void EraseAll(TAirport airport) {
    airports[static_cast<size_t>(airport)].second = 0;
  }

  // получить некоторый объект, по которому можно проитерироваться,
  // получив набор объектов типа Item - пар (аэропорт, количество),
  // упорядоченных по аэропорту
  Items GetItems() const {
    return airports;
  }
};

int main() {
  enum class MoscowAirport {
    VKO,
    SVO,
    DME,
    ZIA,
    Last_
  };

  const vector<MoscowAirport> airports = {
      MoscowAirport::SVO,
      MoscowAirport::VKO,
      MoscowAirport::ZIA,
      MoscowAirport::SVO,
  };
  AirportCounter<MoscowAirport> airport_counter(begin(airports), end(airports));
  for (const auto& [airport, count] : airport_counter.GetItems()) {
    cout << static_cast<size_t>(airport) << ": " << count << '\n';
  }

  return 0;
}