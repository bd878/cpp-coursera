#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

int main() {
  int n = 5;
  cin >> n;

  vector<int> v(n);
  generate(begin(v), end(v), [i = n]() mutable { return i--; });

  const auto print([&v](){
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    cout << endl;
  });

  do {
    print();
  } while (prev_permutation(begin(v), end(v)));

  return 0;
}