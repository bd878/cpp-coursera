#include "database.h"

void Database::RemoveEmptyDates() {
  vector<map<Date, vector<string>>::const_iterator> empty_fields;
  for (auto it = store.begin(); it != store.end(); it++) {
    if (it->second.empty()) {
      empty_fields.push_back(it);
    }
  }

  for (const auto& empty : empty_fields) {
    store.erase(empty);
  }
}

void Database::Add(const Date& date, const string& event) {
  auto same_event = find(store[date].begin(), store[date].end(), event);
  if (same_event == store[date].end()) {
    store[date].push_back(event);
  }
}

void Database::Print(ostream& os) const {
  for (const auto& [date, events] : store) {
    if (!events.empty()) {
      for (const auto& event : events) {
        os << date << ' ' << event << '\n';
      }
    }
  }
}

string Database::Last(const Date& date) const {
  const auto& date_events = upper_bound(store.begin(), store.end(), date, [](const Date& date, const auto& field){
    return date < field.first;
  });

  if (date_events == store.begin()) {
    return "No entries\n";
  }

  ostringstream os;
  os << prev(date_events)->first << ' '
    << prev(date_events)->second.back() << '\n';

  return os.str();
}
