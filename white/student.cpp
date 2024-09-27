#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Student {
  string first_name;
  string last_name;

  unsigned int day;
  unsigned int month;
  unsigned int year;
};

int main() {
  int n;
  cin >> n;

  string first_name, last_name;
  unsigned int day, month, year;
  vector<Student> students;
  students.reserve(n);

  for (size_t i = 0; i < n; ++i) {
    cin >> first_name >> last_name >> day >> month >> year;
    students.push_back(Student{ first_name, last_name, day, month, year });
  }

  unsigned int m;
  cin >> m;
  string request;
  unsigned int student_number;
  for (size_t i = 0; i < m; ++i) {
    cin >> request >> student_number;

    --student_number;

    if (request == "name" && student_number >= 0 && student_number < n) {
      cout << students[student_number].first_name << ' ' << students[student_number].last_name << endl;
    } else if (request == "date" && student_number >= 0 && student_number < n) {
      cout << students[student_number].day << '.' << students[student_number].month << '.' << students[student_number].year << endl;
    } else {
      cout << "bad request" << endl;
    }
  }

  return 0;
}