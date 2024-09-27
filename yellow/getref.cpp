#include <iostream>
#include <stdexcept>
#include <map>

using namespace std;

template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>&, const Key&);


template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& dict, const Key& k) {
  if (dict.count(k) == 0) {
    throw runtime_error("key is not found");
  }

  return dict.at(k);
}

int main() {
  map<int, string> m = {{0, "value"}};
  string& item = GetRefStrict(m, 0);
  item = "newvalue";
  cout << m[0] << endl; // выведет newvalue
  return 0;
}