#include <sstream>
#include <utility>
#include <iostream>

using namespace std;

istringstream GetStream() {
  istringstream is("Immovable movers\n");
  return move(is);
}

int main() {
  istringstream is = GetStream();
  string str;
  getline(is, str);

  cout << str;
  return 0;
}