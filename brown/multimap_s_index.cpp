#include <map>
#include <unordered_map>
#include <functional>
#include <string>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

template <typename Key, typename Value>
struct SecondaryIndex {
  using SecondaryIndexIt = typename multimap<Key, Value>::const_iterator;

  multimap<Key, Value> s_index;

  void insert(Key key, const Value& value) {
    s_index.insert(make_pair(key, value));
  }

  template <typename Callback>
  void GoThrough(Key from, Key to, Callback callback) const {
    SecondaryIndexIt lower = s_index.lower_bound(from);

    if (lower != s_index.end()) {
      SecondaryIndexIt upper = s_index.upper_bound(to);

      for (SecondaryIndexIt it = lower; it != upper; ++it) {
        if (!callback(it)) {
          break;
        }
      }
    }
  }

  template <typename Callback>
  void GoThroughByValue(Key from, Key to, Callback callback) const {
    GoThrough(from, to, [&callback](SecondaryIndexIt it){
      return callback(it->second->second);
    });
  }

  void EraseById(Key from, Key to, const string& id) {
    GoThrough(from, to, [&id, this](SecondaryIndexIt it){
      if (it->second->second.id == id) {
        s_index.erase(it);
        return false;
      }

      return true;
    });
  }
};

int main() {
  SecondaryIndex<int, string> int_index;

  return 0;
}