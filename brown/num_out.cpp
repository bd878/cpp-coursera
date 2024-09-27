#include <iostream>
#include <sstream>

using namespace std;

int main() {
  ostringstream out;
  out << 25;
  cout << "Num out: " << out.str() << '\n';
  return 0;
}