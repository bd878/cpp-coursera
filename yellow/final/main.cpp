#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is) {
  string str;
  is >> ws;
  getline(is, str);
  return str;
}

void TestAll();

int main() {
  TestAll();

  Database db;

  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

Database FulfillDatabase(const string& str) {
  stringstream ss(str);

  Database db;
  for (string line; getline(ss, line); ) {
    istringstream is(line);

    const auto date = ParseDate(is);
    const auto event = ParseEvent(is);

    db.Add(date, event);
  }

  return db;
}

void TestAddDatabase() {
  {
    const auto& db = FulfillDatabase("2020-01-01 new year \n 1961-04-6 space program \n 1945-05-9 victory day");
    ostringstream os;
    db.Print(os);
    AssertEqual(
      os.str(),
      "1945-05-09 victory day\n1961-04-06 space program \n2020-01-01 new year \n",
      "Adds and prints sorted events"
    );
  }
  {
    const auto& db = FulfillDatabase("2017-01-01 Holiday\n2017-03-08 Holiday\n2017-1-1 New Year\n2017-1-1 New Year\n");
    ostringstream os;
    db.Print(os);
    AssertEqual(
      os.str(),
      "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\n",
      "Removes duplicates, prints in correct order"
    );
  }
}

void TestLastDatabase() {
  {
    const auto& db = FulfillDatabase("2017-01-01 New Year\n2017-03-08 Holiday\n2017-01-01 Holiday");
    AssertEqual(db.Last({2016, 12, 31}), "No entries\n", "No entries found");
    AssertEqual(db.Last({2017, 1, 1}), "2017-01-01 Holiday\n", "Finds date");
    AssertEqual(db.Last({2017, 6, 1}), "2017-03-08 Holiday\n", "Finds date");
  }
}

void TestRemoveIfDatabase() {
  {
    Database db = FulfillDatabase("2017-06-01 1st of Junen\n2017-07-08 8th of July\n2017-07-08 Someone's birthday\n");
    const Date d(2017, 7, 8);
    auto pred([d](const Date& date, const string& event){
      return date < d;
    });
    AssertEqual(db.RemoveIf(pred), 1, "Removes entries");

    ostringstream os;
    db.Print(os);
    AssertEqual(
      os.str(),
      "2017-07-08 8th of July\n2017-07-08 Someone's birthday\n",
      "Removes empty dates"
    );
  }
}

void TestFindIfDatabase() {
  {
    Database db = FulfillDatabase("2017-01-01 Holiday\n2017-03-08 Holiday\n2017-01-01 New Year");
    auto pred([](const Date& date, const string& event){
      return event != "working day";
    });
    const auto entries = db.FindIf(pred);
    AssertEqual(entries.size(), 3, "Found correct amount of entries");

    ostringstream os;
    for (const string& entry : entries) {
      os << entry;
    }
    AssertEqual(
      os.str(),
      "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\n",
      "Correct entries found"
    );
  }
}

void TestParseDate() {
  {
    stringstream ss{"2020-05-18 test"};
  
    const auto date = ParseDate(ss);
    ostringstream os;
    os << date;
  
    AssertEqual(os.str(), "2020-05-18", "Parses date from istream");
  }
}

void TestDatabase() {
  TestRunner tr;

  tr.RunTest(TestAddDatabase, "TestAddDatabase");
  tr.RunTest(TestLastDatabase, "TestLastDatabase");
  tr.RunTest(TestRemoveIfDatabase, "TestRemoveIfDatabase");
  tr.RunTest(TestFindIfDatabase, "TestFindIfDatabase");
}

void TestAll() {
  TestRunner tr;

  tr.RunTest(TestDatabase, "TestDatabase");
  tr.RunTest(TestParseDate, "TestParseDate");
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
}
