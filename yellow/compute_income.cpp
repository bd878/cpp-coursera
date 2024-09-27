#include <algorithm>
#include <numeric>
#include <tuple>
#include <exception>
#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>

// #include "income_date.h"

using namespace std;

int ConvertToInt(const string&);
pair<string, string> SplitTwo(string&, char);
string SplitString(string&, char);

class Date {
public:
  static Date fromString(string);
  time_t AsTimestamp() const;
  string Print() const;

private:
  int year;
  int month;
  int day;

  Date(int y, int m, int d)
    : year(y), month(m), day(d) {};
};

int ComputesDaysDiff(const Date&, const Date&);

static const Date START_DATE = Date::fromString("2000-01-01");
static const Date END_DATE = Date::fromString("2100-01-01");
static const int DAY_COUNT = ComputesDaysDiff(END_DATE, START_DATE);

int main() {
  cout.precision(25);
  vector<double> earnings(DAY_COUNT);

  int q;
  cin >> q;

  for (int i = 0; i < q; i++) {
    string command, from, to;
    cin >> command >> from >> to;

    Date from_date = Date::fromString(from);
    Date to_date = Date::fromString(to);

    auto from_it = earnings.begin() + ComputesDaysDiff(from_date, START_DATE);
    auto to_it = earnings.begin() + ComputesDaysDiff(to_date, START_DATE);

    if (command == "Earn") {
      double value;
      cin >> value;

      int days = ComputesDaysDiff(to_date, from_date) + 1;
      double shared_income = value / days;
      transform(from_it, next(to_it), from_it, [&shared_income](const double& v) { return v + shared_income; });
    } else if (command == "ComputeIncome") {
      cout << (accumulate(from_it, next(to_it), 0.0)) << endl;
    } else {
      cout << "Unknown request" << endl;
    }
  }

  return 0;
}

int ConvertToInt(const string& str) {
  size_t pos;
  const int num = stoi(str, &pos);
  if (pos != str.length()) {
    stringstream error;
    error << "string " << str << " contains " << (str.length() - pos) << " trailing chars";
    throw invalid_argument(error.str());
  }
  return num;
}

pair<string, string> SplitTwo(string& str, char delim) {
  const size_t pos = str.find(delim);
  if (pos == string::npos) {
    return {str, ""};
  } else {
    return {str.substr(0, pos), str.substr(pos + 1)};
  }
}

string SplitString(string& str, char delim) {
  const auto [lhs, rhs] = SplitTwo(str, delim);
  str = rhs;
  return lhs;
}

int ComputesDaysDiff(const Date& to, const Date& from) {
  const time_t to_tm = to.AsTimestamp();
  const time_t from_tm = from.AsTimestamp();
  static constexpr int SECONDS_IN_DAY = 60 * 60 * 24;
  return (to_tm - from_tm) / SECONDS_IN_DAY;
}

Date Date::fromString(string str) {
  int year = ConvertToInt(SplitString(str, '-'));
  int month = ConvertToInt(SplitString(str, '-'));
  int day = ConvertToInt(str);

  return {year, month, day};
}

string Date::Print() const {
  stringstream ss;
  ss << year << '-' << month << '-' << day;
  return ss.str();
};

time_t Date::AsTimestamp() const {
  tm timeinfo;
  timeinfo.tm_sec = 0;
  timeinfo.tm_min = 0;
  timeinfo.tm_hour = 0;
  timeinfo.tm_year = year - 1900;
  timeinfo.tm_mon = month - 1;
  timeinfo.tm_mday = day;
  timeinfo.tm_isdst = 0;

  return mktime(&timeinfo);
}