#include <iostream>
#include <iterator>
#include <numeric>
#include <exception>
#include <sstream>
#include <tuple>
#include <ctime>
#include <algorithm>

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

static const Date START_DATE = Date::fromString("1700-01-01");
static const Date END_DATE = Date::fromString("2100-01-01");
static const int DAY_COUNT = ComputesDaysDiff(END_DATE, START_DATE);

int main() {
  vector<uint64_t> money(DAY_COUNT, 0);
  vector<uint64_t> sums(DAY_COUNT, 0);

  uint64_t earncount;
  cin >> earncount;
  for (uint64_t i = 0; i < earncount; ++i) {
    string daystring;
    uint64_t value;
    cin >> daystring >> value;

    Date date = Date::fromString(daystring);
    int day = ComputesDaysDiff(date, START_DATE);
    money[day] += value;
  }

  partial_sum(money.begin(), money.end(), sums.begin());

  uint64_t querycount;
  cin >> querycount;
  for (uint64_t i = 0; i < querycount; ++i) {
    string from, to;
    cin >> from >> to;

    Date date_from = Date::fromString(from);
    Date date_to = Date::fromString(to);
    auto from_it = sums.begin() + ComputesDaysDiff(date_from, START_DATE);
    auto to_it = sums.begin() + ComputesDaysDiff(date_to, START_DATE);

    if (from_it == sums.begin()) {
      cout << *to_it << endl;
    } else {
      cout << (*to_it - *prev(from_it)) << endl;
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