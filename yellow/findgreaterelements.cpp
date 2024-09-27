#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T> elements, const T& border) {
  vector<T> result; 
  const auto& it = find(begin(elements), end(elements), border);
  if (it != end(elements)) {
    copy(next(it), end(elements), back_inserter(result));
  }
  return result;
}

int main() {
  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
    cout << x << " ";
  }
  cout << endl;
  
  string to_find = "Python";
  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
  return 0;
}
