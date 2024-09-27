#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<string> strings(n);
  for (int i = 0; i < n; ++i) {
    cin >> strings[i];
  }

  sort(begin(strings), end(strings), [](auto str1, auto str2) {
    transform(begin(str1), end(str1), begin(str1), [](unsigned char c) { return tolower(c); });
    transform(begin(str2), end(str2), begin(str2), [](unsigned char c) { return tolower(c); });

    return str1 < str2;
  });
  copy(begin(strings), end(strings), ostream_iterator<string>{cout, " "});

  return 0;
}