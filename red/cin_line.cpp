#include <iostream>
#include <sstream>

using namespace std;

int main() {
  istringstream is("Hello, world!");
  istringstream is2("Bye!");

  string str;
  getline(is, str);
  stringstream ss(str);
  cout << ss.str() << '\n';
  getline(is2, str);
  cout << str << '\n';

  return 0;
}