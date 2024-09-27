#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

template <typename T> T Sqr(T value);
template <typename T> vector<T> Sqr(const vector<T>&);
template <typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>&);
template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>&);

template <typename T> T Sqr(T value) {
  return value * value;
}

template <typename T>
vector<T> Sqr(const vector<T>& value) {
  vector<T> result;
  for (const auto& v : value)
    result.push_back(Sqr(v));
  return result;
}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& value) {
  map<Key, Value> result;
  for (const auto& [k, v] : value)
    result[k] = Sqr(v);

  return result;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& value) {
  return {Sqr(value.first), Sqr(value.second)};
}

int main() {
  vector<int> v = {1, 2, 3};
  cout << "vector:";
  for (int x : Sqr(v)) {
    cout << ' ' << x;
  }
  cout << endl;

  map<int, pair<int, int>> map_of_pairs = {
    {4, {2, 2}},
    {7, {4, 3}}
  };
  cout << "map of pairs:" << endl;
  for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
  }
  return 0;
}