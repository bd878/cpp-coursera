#pragma once

#include <string>
#include <iostream>
#include <exception>
#include <sstream>
#include <tuple>

using namespace std;

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

struct Date {
  int year, month, day;
};

bool operator<(const Date& l, const Date& r) {
  return (
    l.year == r.year
      ? l.month == r.month
        ? l.day < r.day
        : l.month < r.month
      : l.year < r.year
  );
}

bool operator==(const Date& l, const Date& r) {
  return (l.year == r.year && l.month == r.month && l.day == r.day);
}

ostream& operator<<(ostream& os, const Date& d) {
  os << d.year << '-' << d.month << '-' << d.day;
  return os;
}

istream& operator>>(istream& is, Date& d) {
  string str;
  is >> str;

  d.year = ConvertToInt(SplitString(str, '-'));
  d.month = ConvertToInt(SplitString(str, '-'));
  d.day = ConvertToInt(str);

  return is;
}

struct Time {
  int hours, minutes;
};

bool operator<(const Time& l, const Time& r) {
  return (
    l.hours == r.hours
      ? l.minutes < r.minutes
      : l.hours < r.hours
  );
}

bool operator==(const Time& l, const Time& r) {
  return (l.hours == r.hours && l.minutes == r.minutes);
}

ostream& operator<<(ostream& os, const Time& t) {
  os << t.hours << ':' << t.minutes;
  return os;
}

istream& operator>>(istream& is, Time& t) {
  string str;
  is >> str;

  t.hours = ConvertToInt(SplitString(str, ':'));
  t.minutes = ConvertToInt(str);

  return is;
}

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  int price;
};
