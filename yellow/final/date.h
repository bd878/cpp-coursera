#pragma once

#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

int ConvertToInt(const string&);
pair<string, string> SplitTwo(string&, char);
string SplitString(string&, char);

class Date {
private:
  int year;
  int month;
  int day;

public:
  Date(int y, int m, int d)
    : year(y), month(m), day(d) {};

  time_t AsTimestamp() const;
  bool operator<(const Date&) const;
  bool operator>(const Date&) const;
  bool operator<=(const Date&) const;
  bool operator>=(const Date&) const;
  bool operator==(const Date&) const;
  bool operator!=(const Date&) const;
  friend ostream& operator<<(ostream&, const Date&);
};

Date ParseDate(istream& is);
int ComputesDaysDiff(const Date&, const Date&);
