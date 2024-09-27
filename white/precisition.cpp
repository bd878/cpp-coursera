#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
  fstream fin;
  fin.open("input.txt");
  if (!fin.is_open()) {
    return 1;
  }

  vector<double> nums;
  istream_iterator<double> it{fin};
  istream_iterator<double> end_it;
  copy(it, end_it, inserter(nums, nums.end()));
  for (const double& num : nums) {
    cout << fixed << setprecision(3) << num << endl;
  }
  return 0;
}