#include <set>
#include <string>
#include <map>

using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m) {
  set<string> values;
  for (auto& [key, value] : m) {
    values.insert(value);
  }
  return values;
}