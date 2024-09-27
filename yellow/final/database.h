#pragma once

#include <ostream>
#include <algorithm>
#include <map>
#include <vector>
#include <functional>
#include <exception>

#include "date.h"

using namespace std;

class Database {
private:
  map<Date, vector<string>> store;

  void RemoveEmptyDates();
public:
  void Add(const Date&, const string&);
  void Print(ostream&) const;
  string Last(const Date&) const;

  template <typename Pred>
  int RemoveIf(Pred&);

  template <typename Pred>
  vector<string> FindIf(Pred&) const;
};

template <typename Pred>
int Database::RemoveIf(Pred &pred) {
  int removed = 0;
  for (auto& [date, events] : store) {
    const auto& new_end = remove_if(events.begin(), events.end(), [&pred, &date](const string& event){
      return pred(date, event);
    });
    removed += distance(new_end, events.end());
    events.erase(new_end, events.end());
  }

  RemoveEmptyDates();

  return removed;
}

template <typename Pred>
vector<string> Database::FindIf(Pred &pred) const {
  vector<string> result;
  for (auto& [date, events] : store) {
    for (const auto& event : events) {
      if (pred(date, event)) {
        ostringstream os;
        os << date << ' ' << event << '\n';

        result.push_back(os.str());
      }
    }
  }

  return result;
}
