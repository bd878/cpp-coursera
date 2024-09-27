#include "test_runner.h"

#include <utility>
#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

// Реализуйте этот класс
class Database {
  using IndexIt = unordered_map<string, Record>::const_iterator;

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

  unordered_map<string, Record> index;
  SecondaryIndex<int, IndexIt> timestamp_index;
  SecondaryIndex<int, IndexIt> karma_index;
  SecondaryIndex<string, IndexIt> user_index;
public:
  bool Put(const Record& record);
  const Record* GetById(const string& id) const;
  bool Erase(const string& id);

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const;

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const;

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const;
};

bool Database::Put(const Record& record) {
  const auto [it, inserted] = index.insert(make_pair(record.id, record));

  if (inserted) {
    timestamp_index.insert(record.timestamp, it);
    karma_index.insert(record.karma, it);
    user_index.insert(record.user, it);
  }

  return inserted;
}

const Record* Database::GetById(const string& id) const {
  const auto it = index.find(id);
  if (it == index.end()) {
    return nullptr;
  } else {
    return &(it->second);
  }
}

bool Database::Erase(const string& id) {
  const auto index_it = index.find(id);
  if (index_it == index.end()) {
    return false;
  }

  timestamp_index.EraseById(index_it->second.timestamp, index_it->second.timestamp, id);
  karma_index.EraseById(index_it->second.karma, index_it->second.karma, id);
  user_index.EraseById(index_it->second.user, index_it->second.user, id);

  index.erase(index_it);
  return true;
}

template <typename Callback>
void Database::RangeByTimestamp(int low, int high, Callback callback) const {
  timestamp_index.GoThroughByValue(low, high, callback);
}

template <typename Callback>
void Database::RangeByKarma(int low, int high, Callback callback) const {
  karma_index.GoThroughByValue(low, high, callback);
}

template <typename Callback>
void Database::AllByUser(const string& user, Callback callback) const {
  user_index.GoThroughByValue(user, user, callback);
}

void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}
