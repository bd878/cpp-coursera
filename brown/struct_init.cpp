#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Building {
  int num;
  string street;

  friend ostream& operator<<(ostream& out, const Building& b) {
    out << b.num << ' ' << b.street << '\n';
    return out;
  }
};

int main() {
  cout << Building{25, "Gagarin"};
  return 0;
}