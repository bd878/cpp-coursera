#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Person {
 public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }

  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }

  string GetFullName(int year) {
    string first_name = FindName(year, first_names);
    string last_name = FindName(year, last_names);

    if (first_name.empty() && last_name.empty()) {
      return "Incognito";
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";
    }

    return first_name + " " + last_name;
  }

  string GetFullNameWithHistory(int year) {
    string first_name = FindName(year, first_names);
    string last_name = FindName(year, last_names);

    string first_name_history = StringifyHistory(GetNameHistory(first_names, first_name, year));
    string last_name_history = StringifyHistory(GetNameHistory(last_names, last_name, year));

    if (first_name.empty() && last_name.empty()) {
      return "Incognito";
    } else if (first_name.empty()) {
      return last_name + " " + last_name_history + "with unknown first name";
    } else if (last_name.empty()) {
      return first_name + " " + first_name_history + "with unknown last name";
    }

    return first_name + " " + first_name_history + last_name + " " + last_name_history;
  }

 private:
  map<int, string> first_names;
  map<int, string> last_names;

  string FindName(int year, map<int, string> names) {
    string name = "";
    for (const auto& [y, n] : names) {
      if (y <= year) {
        name = n;
      } else {
        break;
      }
    }
    return name;
  }

  vector<string> GetNameHistory(const map<int, string>& names, string current_name, int year) {
    vector<string> result;

    for (const auto& [y, n] : names) {
      if (y > year) {
        break;
      }

      if (count(begin(result), end(result), n) == 0) {
        result.push_back(n);
      }
    }

    if (result.size() > 0 && result.back() == current_name) {
      result.pop_back();
    }

    reverse(begin(result), end(result));

    return result;
  }

  string StringifyHistory(const vector<string>& history) {
    string result = "";

    if (history.size() > 0) {
      result = "(";

      for (const auto& n : history) {
        result += n + ", ";
      }

      result.erase(result.size() - 2);
      result += ") ";
    }

    return result;
  }
};

int main() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeFirstName(1965, "Appolinaria");

  person.ChangeLastName(1965, "Sergeeva");
  person.ChangeLastName(1965, "Volkova");
  person.ChangeLastName(1965, "Volkova-Sergeeva");

  for (int year : {1964, 1965, 1966}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}