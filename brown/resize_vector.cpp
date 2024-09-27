#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  vector<int> v = {0};
  v.resize(11);
  v[10] = 25;
  cout << "v.size(): " << v.size() << '\n';
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
  return 0;
}