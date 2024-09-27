#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> temperatures(n);
  int sum = 0;
  for (int& temp : temperatures) {
    cin >> temp;
    sum += temp;
  }

  int ave = sum / temperatures.size();
  vector<int> indexes;
  for (vector<int>::size_type i = 0; i < temperatures.size(); ++i) {
    if (temperatures.at(i) > ave) {
      indexes.push_back(i);
    }
  }

  cout << indexes.size() << endl;
  for (int& above_ave_index : indexes)
    cout << above_ave_index << " ";

  return 0;
}