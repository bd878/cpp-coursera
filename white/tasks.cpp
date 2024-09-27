#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
  fstream fin;
  fin.open("./tasks.txt");
  if (!fin.is_open()) {
    exit(EXIT_FAILURE);
    return 1;
  }

  int current_month_number = 0;
  const vector<int> months{31, 28, 31, 30, 31, 30, 31, 29, 30, 31, 31, 30};
  vector<vector<string>> tasks{31};

  auto dump([&tasks](int day_number) {
    cout << tasks.at(day_number).size() << ' ';
    for (const auto& task : tasks.at(day_number))
      cout << task << ' ';
    cout << '\n';
  });

  int commands_count;
  fin >> commands_count;
  string command;
  for (int i = 0; i < commands_count; ++i) {
    fin >> command;
    if (command == "DUMP") {
      int day_number;
      fin >> day_number;
      if (day_number > tasks.size()) {
        cout << 0 << '\n';
      } else {
        dump(day_number - 1);
      }
    } else if (command == "ADD") {
      string task;
      int day_number;
      fin >> day_number >> task;
      tasks.at(day_number - 1).push_back(task);
    } else if (command == "NEXT") {
      ++current_month_number;
      if (current_month_number == months.size())
        current_month_number = 0;

      int days_count = months.at(current_month_number);
      if (tasks.size() > days_count) {
        for (int j = days_count; j < tasks.size(); ++j) {
          auto& last_day_tasks = tasks.at(days_count - 1);
          auto& day_tasks = tasks.at(j);
          last_day_tasks.insert(end(last_day_tasks), begin(day_tasks), end(day_tasks));
        }
      }

      tasks.resize(days_count);
    }
  }

  return 0;
}