#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>

using namespace std;

int main() {
  fstream fin("avetemp.txt");

  int64_t n, sum = 0;
  fin >> n;

  vector<int64_t> temps(n);
  for (int64_t& temp : temps) {
    fin >> temp;
    sum += temp;
  }

  double ave = sum / static_cast<double>(temps.size());

  vector<int> indexes;
  for (size_t i = 0; i < temps.size(); ++i)
    if (temps.at(i) > ave)
      indexes.push_back(i);

  cout << indexes.size() << ' ';
  for (int i : indexes)
    cout << i << ' ';

  cout << endl;

  return 0;
}