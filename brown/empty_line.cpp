#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
  stringstream is(R"(HTTP/1.1 200 OK
Content-Length: 2

12
  )");

  string line;
  getline(is, line);

  istringstream code_input(line);
  string dummy;
  int status_code;
  code_input >> dummy >> status_code;

  cout << "Dummy: " << dummy << '\n';
  cout << "Status code: " << status_code << '\n';

  while (getline(is, line) && !line.empty()) {
    cout << "Parsed line: " << line << '\n';
  }

  return 0;
}