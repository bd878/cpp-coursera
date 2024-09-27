#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
  vector<string> result;
  for (auto it = begin(s); it != end(s); it = find(it, end(s), ' ')) {
    if (*it == ' ') {
      it = next(it);
    }
    auto next_it = find(it, end(s), ' ');
    string s{it, next_it};
    result.push_back(s);
  }
  return result;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}