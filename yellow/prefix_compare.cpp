#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

int main() {
  vector<string> cities{"anadyr", "moscow", "murmansk", "kazan"};
  string prefix = "mo";

  auto lower_it = lower_bound(cities.begin(), cities.end(), prefix, [](const auto& item, const string& p){
    size_t count = min(item.length(), p.length());
    return lexicographical_compare(item.begin(), item.begin() + count, p.begin(), p.begin() + count);
  });
  auto upper_it = upper_bound(cities.begin(), cities.end(), prefix, [](const string& p, const auto& item){
    size_t count = min(item.length(), p.length());
    return lexicographical_compare(p.begin(), p.begin() + count, item.begin(), item.begin() + count);
  });

  cout << (*lower_it) << ' ' << (*upper_it) << endl;
  return 0;
}