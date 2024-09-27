#include <iostream>
#include <ctime>
#include <exception>
#include <sstream>

#include "income_date.h"
#include "test_runner.h"

using namespace std;

void ParsesDateFromString() {
  for (int i = 10; i--; ) {
    int year = GetRandomInt(2000, 2099);
    int month = GetRandomInt(1, 12);
    int day = GetRandomInt(1, 31);

    ostringstream ss;
    ss << year << "-" << month << '-' << day;
    const auto d = Date::fromString(ss.str());
    AssertEqual(d.Print(), ss.str(), "Print date correctly");
  }
}

void FailesToParseWrongString() {
  string wrongDate = "2020-15aaa-16";
  try {
    const auto d = Date::fromString(wrongDate);
    throw runtime_error("should fail on wrong date string");
  } catch (invalid_argument& e) {
    AssertEqual(string(e.what()), "string 15aaa contains 3 trailing chars", "Should fail on parsing wrong date");
  }
}

void ConvertsToTimestamp() {
  for (int i = 10; i--; ) {
    int year = GetRandomInt(2000, 2099);
    int month = GetRandomInt(1, 12);
    int day = GetRandomInt(1, 31);

    ostringstream ss;
    ss << year << "-" << month << '-' << day;
    const auto d = Date::fromString(ss.str());
    Assert(d.AsTimestamp() != -1, "Represents date as timestamp");
  }
}

void FindsDayDiff() {
  for (int i = 10; i--; ) {
    int year = GetRandomInt(2000, 2098);
    int month = GetRandomInt(1, 11);
    int day = GetRandomInt(1, 30);

    ostringstream ssfrom;
    ssfrom << year << "-" << month << "-" << day;
    ostringstream ssto;
    ssto << year << "-" << month << "-" << (day + 1);
    const auto dfrom = Date::fromString(ssfrom.str());
    const auto dto = Date::fromString(ssto.str());
    AssertEqual(ComputesDaysDiff(dto, dfrom), 1, "Computes 1 day diff");
  }
}

void DaysBoundaries() {
  const auto dfrom = Date::fromString("1700-05-18");
  const auto dto = Date::fromString("1700-05-19");
  AssertEqual(ComputesDaysDiff(dto, dfrom), 1, "Computes 1 day diff after 1900 year");
}

int main() {
  TestRunner runner;

  runner.RunTest(ParsesDateFromString, "ParsesDateFromString");
  runner.RunTest(FailesToParseWrongString, "FailesToParseWrongString");
  runner.RunTest(ConvertsToTimestamp, "ConvertsToTimestamp");
  runner.RunTest(FindsDayDiff, "FindsDayDiff");
  runner.RunTest(DaysBoundaries, "DaysBoundaries");

  return 0;
}