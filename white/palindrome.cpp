#include <string>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

// tutorial example
bool isPalindromeShort(string str) {
  for (int i = 0; i < str.size() / 2; ++i) {
    if (str[i] != str[str.size() - i - 1]) {
      return false;
    }
  }
  return true;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " ...words" << endl;
    return 1;
  }

  vector<string> words;
  copy(argv + 1, argv + argc, back_inserter(words));

  auto isPalindrome([](const string& str){
    string half = str.substr(0, str.length() / 2);
    reverse(begin(half), end(half));
    size_t found = str.find(half, half.length());
    return found != string::npos;
  });

  for (const auto &word : words) {
    const string palindrome = isPalindromeShort(word) ? " " : " not ";
    cout << word << " is" << palindrome << "a palindrome" << '\n';
  }

  return 0;
}
