#include <exception>
#include <sstream>
#include <tuple>

#include "income_date.h"

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