#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
  unordered_map<int, vector<string>> romes({
    {2, {"Constantinopol"}},
    {3, {"Rome"}}
  });

  romes.insert(make_pair(1, vector<string>()));
  vector<string>* msc = &romes.at(1);
  msc->push_back("Moscow");

  const vector<string>& ptr = romes.at(1);
  copy(ptr.begin(), ptr.end(), ostream_iterator<string>(cout, " "));
  cout << endl;

  return 0;
}
