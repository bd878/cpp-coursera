#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

int main() {
  vector<int> test{1, 2, 3};

  cout << *prev(test.end()) << '\n';
  cout << *test.rbegin() << '\n';

  return 0;
}