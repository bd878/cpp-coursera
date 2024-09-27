#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

int main() {
  fstream fin("input.txt");

  int n, m;
  fin >> n >> m;
  fin.get(); // skip new line
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      string a;

      if (j + 1 < m) {
        getline(fin, a, ',');
      } else {
        getline(fin, a);
      }

      cout << setw(10) << a;
      if (j + 1 < m) {
        cout << ' ';
      }
    }

    if (i + 1 < n) {
      cout << endl;
    }
  }

  return 0;
}