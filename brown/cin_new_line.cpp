#include <sstream>
#include <string>
#include <iostream>

using namespace std;

int main() {
  stringstream ss;
  ss << '\n';

  string str;
  if (ss >> str) {
    cout << "New line is true";
  } else {
    cout << "New line is false";
  }

  cout << endl;

  return 0;
}
