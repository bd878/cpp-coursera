#include <iostream>
#include <fstream>
#include <map>

using namespace std;

map<char, int> BuildCharCounters(const string& str) {
  map<char, int> char_counter;
  for (const char ch : str) {
    ++char_counter[ch];
  }
  return char_counter;
}

int main() {
  fstream fin;
  fin.open("anagrams.txt");
  if (!fin.is_open()) {
    exit(EXIT_FAILURE);
    return 1;
  }

  string word1;
  string word2;

  int pairs_count;
  fin >> pairs_count;
  for (int i = 0; i < pairs_count; ++i) {
    fin >> word1 >> word2;
    if (BuildCharCounters(word1) == BuildCharCounters(word2)) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }

  return 0;
}