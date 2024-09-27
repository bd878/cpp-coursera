#include <fstream>
#include <iostream>

using namespace std;

int main() {
  fstream fin("testempty.txt");
  string first;
  fin >> first;
  cout << first;
  string test;
  if (getline(fin, test)) {
    cout << "Read successfully <" << test << "> string" << endl;
    if (test.empty()) {
      cout << "empty" << endl;
    }
  } else {
    cout << "Failed to read test string" << endl;
  }

  return 0;
}