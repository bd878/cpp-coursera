#pragma once

#include <iostream>
#include <ctime>
#include <sstream>

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
