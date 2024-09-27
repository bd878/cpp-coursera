#pragma once

#include <utility>
#include <iostream>

namespace RAII {
template <typename Provider>
class Booking {
private:
  Provider* provider;
  int* counter;
public:
  Booking() = delete;
  Booking(Provider* p, int& c) 
    : provider(p), counter(&c) {};
  Booking(Booking& b) {
    counter = b.counter;
    provider = b.provider;
    b.counter = nullptr;
  }
  Booking(Booking&& b) {
    counter = b.counter;
    provider = b.provider;
    b.counter = nullptr;
  }
  Booking(const Booking&) = delete;
  Booking& operator=(const Booking& b) = delete;
  Booking& operator=(Booking&& b) {
    b.counter = nullptr;
  };
  ~Booking() {
    if (counter != nullptr) {
      provider->CancelOrComplete(*this);
    }
  }
};
}
