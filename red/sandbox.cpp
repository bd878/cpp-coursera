#include <vector>
#include <iterator>
#include <tuple>
#include <iostream>

using namespace std;

template <typename T>
typename vector<T>::iterator partAndPos(vector<T>& v, size_t index) {
  typename vector<T>::iterator it = v.begin();
  advance(it, index);
  return it;
}

int main() {
  vector<string> s{"abc", "cde", "fgh"};
  auto res = partAndPos(s, 1);
  // *res = "aaa";
  cout << (*res);
  cout << endl;
  return 0;
}
