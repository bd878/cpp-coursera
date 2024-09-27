#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <set>

using namespace std;

template <typename String>
using Char = typename String::value_type;

template <typename String>
using Group = vector<String>;

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
  using UniqChars = set<Char<String>>;

  map<UniqChars, Group<String>> groups;
  for (auto& str : strings) {
    UniqChars chars;
    for (auto& ch : str) {
      chars.insert(move(ch));
    }

    groups[move(chars)].push_back(move(str));
  }

  vector<Group<String>> result;
  result.reserve(groups.size());
  for (auto& group_pair : groups) {
    result.push_back(move(group_pair.second));
  }

  return result;
}

int main() {
  vector<string> strings{"caab", "abc", "cccc", "bacc", "c"};

  auto result = GroupHeavyStrings(strings);
  for (const auto& words : result) {
    cout << words.size() << '\n';
    for (const auto& str : words) {
      cout << str << ' ';
    }
    cout << '\n';
  }

  return 0;
}