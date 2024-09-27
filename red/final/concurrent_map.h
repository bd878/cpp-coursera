#pragma once

#include <utility>
#include <vector>
#include <mutex>
#include <tuple>
using namespace std;

template <typename K, typename V>
class ConcurrentMap {
public:
  static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

  explicit ConcurrentMap(size_t bucket_count)
    : buckets(bucket_count),
      data(bucket_count) {};

  struct Access {
    lock_guard<mutex> g;
    V& ref_to_value;
  };

  Access operator[](const K& key) {
    mutex m;
    lock_guard<mutex> g(m);

    auto& [bucket_mutex, bucket] = data[key % buckets];
    return {lock_guard(bucket_mutex), bucket[key]};
  }

  map<K, V> BuildOrdinaryMap() {
    mutex m;
    lock_guard<mutex> g(m);

    map<K, V> result;
    for (auto& [mu, map_bucket] : data) {
      lock_guard<mutex> bucket_guard(mu);

      for (const auto& [key, value] : map_bucket) {
        result[key] = value;
      }
    }

    return result;
  }
private:
  size_t buckets;
  vector<pair<mutex, map<K, V>>> data;
};
