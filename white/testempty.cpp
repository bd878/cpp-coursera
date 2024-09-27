#include <iostream>
#include <sstream>

using namespace std;

int main() {
  string command;
  while (getline(cin, command)) {
    // Считайте команды с потока ввода и обработайте каждую
    stringstream ss{command};
    string event, date, action;
    ss >> event >> date >> action;
    cout << "Read " << event << ' ' << date << ' ' << action << '\n';
  }

  return 0;
}