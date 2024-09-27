#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

class Person {
private:
  vector<pair<int, string>> first_name_history;
  vector<pair<int, string>> last_name_history;

  void Sort(vector<pair<int, string>>& history);
  string GetName(int year, const vector<pair<int, string>>& history) const;
  vector<string> GetNameHistory(int year, const string& name, const vector<pair<int, string>>& history) const;
public:
  void ChangeFirstName(int year, const string& first_name);
  void ChangeLastName(int year, const string& last_name);
  string GetFullName(int year) const;
  string GetFullNameWithHistory(int year) const;
};

void Person::Sort(vector<pair<int, string>>& history) {
  sort(begin(history), end(history), [](const auto& pair1, const auto& pair2) {
    return pair1.first > pair2.first;
  });
}

string Person::GetName(int year, const vector<pair<int, string>>& history) const {
  const auto& name_pair = upper_bound(begin(history), end(history), year, [](int year, const auto& name_pair) {
    return name_pair.first < year;
  });

  if (name_pair == begin(history)) {
    return "";
  }

  return prev(name_pair)->second;
}

vector<string> Person::GetNameHistory(int year, const string& name, const vector<pair<int, string>>& history) const {
  vector<string> result;
  for (int i = 0; i < history.size(); ++i) {
    const auto& history_pair = history.at(i);
    if (history_pair.first > year) {
      continue;
    }

    if (history_pair.second == name && result.empty()) {
      continue;
    }

    const auto& found = find(begin(result), end(result), history_pair.second);
    if (found == end(result)) {
      result.push_back(history_pair.second);
    }
  }

  return result;
}

void Person::ChangeFirstName(int year, const string& first_name) {
  first_name_history.push_back({ year, first_name });
  Sort(first_name_history);
}

void Person::ChangeLastName(int year, const string& last_name) {
  last_name_history.push_back({ year, last_name });
  Sort(last_name_history);
}

string Person::GetFullName(int year) const {
  const auto& first_name = GetName(year, first_name_history);
  const auto& last_name = GetName(year, last_name_history);

  if (!first_name.empty() && last_name.empty()) {
    return first_name + " with unknown last name";
  } else if (first_name.empty() && !last_name.empty()) {
    return last_name + " with unknown first name";
  } else if (!first_name.empty() && !last_name.empty()) {
    return first_name + " " + last_name;
  }

  return "Incognito";
}

string Person::GetFullNameWithHistory(int year) const {
  const auto& first_name = GetName(year, first_name_history);
  const auto& last_name = GetName(year, last_name_history);
  const auto& first_n_history = GetNameHistory(year, first_name, first_name_history);
  const auto& last_n_history = GetNameHistory(year, last_name, last_name_history);

  auto to_string([](const vector<string>& history, const string& except)->string {
    string result;
    for (int i = 0; i < history.size(); ++i) {
      const auto& str = history[i];
      string trailing = (i + 1 < history.size()) ? ", " : "";
      result = result + str + trailing;
    }

    if (result.empty()) {
      return "";
    }

    return " (" + result + ")";
  });

  if (!first_name.empty() && last_name.empty()) {
    return first_name + to_string(first_n_history, first_name) + " with unknown last name";
  } else if (first_name.empty() && !last_name.empty()) {
    return last_name + to_string(last_n_history, last_name) + " with unknown first name";
  } else if (!first_name.empty() && !last_name.empty()) {
    return first_name + to_string(first_n_history, first_name) + " " + last_name + to_string(last_n_history, last_name);
  }

  return "Incognito";
}

int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  return 0;
}