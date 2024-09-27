#include <map>
#include <fstream>
#include <iostream>

using namespace std;

class CountriesTable {
private:
  map<string, string> countries;
public:
  void changeCapital(const string&, const string&);
  void renameCountry(const string&, const string&);
  void aboutCountry(const string&) const;
  void dump() const;
};

void CountriesTable::changeCapital(const string& country, const string& new_capital) {
  pair<map<string, string>::iterator, bool> x = countries.insert(pair<string, string>(country, new_capital));

  if (x.second) {
    cout << "Introduce new country " << country << " with capital " << new_capital << endl;
  } else {
    if (x.first->second == new_capital) {
      cout << "Country " << country << " hasn't changed its capital" << endl;
    } else {
      cout << "Country " << country << " has changed its capital from "
        << x.first->second << " to " << new_capital << endl;
      countries[country] = new_capital;
    }
  }
}

void CountriesTable::renameCountry(const string& country, const string& new_country) {
  map<string, string>::iterator country_iter = countries.find(country);
  if (country_iter == countries.end() || country == new_country || countries.find(new_country) != countries.end()) {
    cout << "Incorrect rename, skip" << endl;
  } else {
    cout << "Country " << country << " with capital " << country_iter->second << " has been renamed to " << new_country << endl;
    countries[new_country] = country_iter->second;
    countries.erase(country_iter);
  }
}

void CountriesTable::aboutCountry(const string& country) const {
  if (countries.find(country) == countries.end()) {
    cout << "Country " << country << " doesn't exist" << endl;
  } else {
    cout << "Country " << country << " has capital " << countries.at(country) << endl;
  }
}

void CountriesTable::dump() const {
  if (countries.empty()) {
    cout << "There are no countries in the world" << endl;
  } else {
    for (const auto& [country, capital] : countries) {
      cout << country << "/" << capital << endl;
    }
  }
}

int main() {
  CountriesTable table;

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string command;
    cin >> command;
    if (command == "CHANGE_CAPITAL") {
      string country;
      string new_capital;

      cin >> country >> new_capital;
      table.changeCapital(country, new_capital);
    } else if (command == "RENAME") {
      string country;
      string new_country;

      cin >> country >> new_country;
      table.renameCountry(country, new_country);
    } else if (command == "ABOUT") {
      string country;
      cin >> country;
      table.aboutCountry(country);
    } else if (command == "DUMP") {
      table.dump();
    } else {
      cout << "Unknown command " << command << endl;
    }
  }

  return 0;
}