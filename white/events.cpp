#include <iostream>
#include <exception>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>
#include <set>

using namespace std;

void SkipDash(stringstream& ss) {
  if (ss.peek() != '-') {
    throw exception();
  }

  ss.ignore(1);
}

class Date {
private:
  int year;
  int month;
  int day;
public:
  Date(): year{0}, month{0}, day{0} {};
  Date(int y, int m, int d);
  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;
  friend istream& operator>>(istream&, Date&);
  friend ostream& operator<<(ostream&, const Date&);
};

Date::Date(int y, int m, int d) {
  if (m < 1 || m > 12) {
    throw invalid_argument("Month value is invalid: " + to_string(m));
  }

  if (d < 1 || d > 31) {
    throw invalid_argument("Day value is invalid: " + to_string(d));
  }

  year = y;
  month = m;
  day = d;
}

int Date::GetYear() const {
  return year;
}

int Date::GetMonth() const {
  return month;
}

int Date::GetDay() const {
  return day;
}

istream& operator>>(istream& is, Date& d) {
  string date_string;
  is >> date_string;
  stringstream ss{date_string};

  int year, month, day;
  try {
    ss >> year;
    SkipDash(ss);
    ss >> month;
    SkipDash(ss);
    ss >> day;
  } catch (exception& e) {
    throw domain_error("Wrong date format: " + date_string);
  }

  d = Date{year, month, day};

  return is;
}

ostream& operator<<(ostream& os, const Date& d) {
  os << setfill('0');
  os << setw(4) << d.GetYear() << '-'
    << setw(2) << d.GetMonth() << '-'
    << setw(2) << d.GetDay();
  return os;
}

bool operator<(const Date& lhs, const Date& rhs) {
  return (
    lhs.GetYear() == rhs.GetYear()
      ? lhs.GetMonth() == rhs.GetMonth()
        ? lhs.GetDay() < rhs.GetDay()
        : lhs.GetMonth() < rhs.GetMonth()
      : lhs.GetYear() < rhs.GetYear()
  );
}

class Database {
private:
  map<Date, set<string>> events;
public:
  void AddEvent(const Date&, const string&);
  bool DeleteEvent(const Date&, const string&);
  int DeleteDate(const Date&);
  set<string> Find(const Date&) const;
  void Print() const;
};

void Database::AddEvent(const Date& date, const string& event) {
  events[date].insert(event);
}

set<string> Database::Find(const Date& date) const {
  if (events.count(date) > 0) {
    return events.at(date);
  }

  return {};
}

void Database::Print() const {
  for (const auto& [date, date_events] : events) {
    if (!date_events.empty()) {
      cout << date;
    }

    for (const auto& date_event : date_events) {
      cout << ' ' << date_event;
    }

    cout << '\n';
  }
}

bool Database::DeleteEvent(const Date& date, const string& event) {
  if (events.count(date) && events.at(date).count(event)) {
    events.at(date).erase(event);
    return true;
  }

  return false;
}

int Database::DeleteDate(const Date& date) {
  int events_count = 0;
  if (events.count(date)) {
    events_count = events.at(date).size();
    events.erase(events.find(date));
  }

  return events_count;
}

int main() {
  Database db;

  string line;
  while (getline(cin, line)) {
    string command, event;
    Date date;

    stringstream ss{line};

    ss >> command;
    try {
      if (command == "Add") {
        if (ss >> date && ss >> event) {
          db.AddEvent(date, event);
        }
      } else if (command == "Del") {
        if (ss >> date) {
          if (ss >> event) {
            if (db.DeleteEvent(date, event)) {
              cout << "Deleted successfully" << endl;
            } else {
              cout << "Event not found" << endl;
            }
          } else {
            cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
          }
        }
      } else if (command == "Find") {
        if (ss >> date) {
          const set<string> events = db.Find(date);
          for (const string& event : events) cout << event << '\n';
        }
      } else if (command == "Print") {
        db.Print();
      } else if (command == "") {
        continue;
      } else {
        cout << "Unknown command: " << command << endl;
      }
    } catch (exception& e) {
      cout << e.what() << endl;
    }
  }

  return 0;
}