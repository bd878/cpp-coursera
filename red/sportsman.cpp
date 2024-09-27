#include <vector>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

int main() {
  int count;
  cin >> count;

  list<int> sportsmen;
  vector<list<int>::const_iterator> refs(count + 1, sportsmen.end());

  for (int i = 0; i < count; ++i) {
    int first, second;
    cin >> first >> second;
    refs[first] = sportsmen.insert(refs[second], first);
  }

  for (auto& sportsman : sportsmen) {
    cout << sportsman << '\n';
  }

  return 0;
}