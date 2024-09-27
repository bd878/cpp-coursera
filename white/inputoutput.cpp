#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
  ifstream fin;
  ofstream fout;
  fin.open("input.txt");
  fout.open("output.txt");
  if (!fin.is_open()) {
    return 1;
  }

  if (!fout.is_open()) {
    return 1;
  }

  string str;
  while (getline(fin, str)) {
    fout << str << endl;
  }
  fout << endl;

  return 0;
}