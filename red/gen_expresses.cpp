#include <fstream>

#include "test_runner.h"

using namespace std;

int main() {
  ofstream fout("add_expresses.txt");
  int COUNT = 10e4;
  int STATIONS = 10e9;

  fout << COUNT << '\n';
  for (int i = 0; i < COUNT; i++) {
    fout << GetRandomInt(-STATIONS, STATIONS) << ' '
      << GetRandomInt(-STATIONS, STATIONS) << '\n';
  }

  ofstream fout2("go_expresses.txt");
  fout2 << COUNT << '\n';
  for (int i = 0; i < COUNT; i++) {
    fout2 << GetRandomInt(-STATIONS, STATIONS) << ' '
      << GetRandomInt(-STATIONS, STATIONS) << '\n';
  }

  return 0;
}