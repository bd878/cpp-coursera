#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

int main() {
  vector<int> v;
  if (*prev(end(v)) == v.back()) {
    cout << "end is back";
  } else {
    cout << "end is not back";
  }
  cout << endl;
  return 0;
}