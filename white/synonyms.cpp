#include <iostream>
#include <fstream>
#include <set>
#include <map>

using namespace std;

class Synonyms {
private:
  map<string, set<string>> words;
public:
  void add(const string&, const string&);
  int count(const string&) const;
  int check(const string&, const string&) const;
};

void Synonyms::add(const string& word1, const string& word2) {
  words[word1].insert(word2);
  words[word2].insert(word1);
}

int Synonyms::count(const string& word) const {
  if (words.count(word)>0)
    return words.at(word).size();
  return 0;
}

int Synonyms::check(const string& word1, const string& word2) const {
  if (words.count(word1)>0 && words.count(word2)>0) {
    if (words.at(word1).find(word2) != words.at(word1).end() && words.at(word2).find(word1) != words.at(word2).end()) {
      return 1;
    }
  }

  return 0;
}

int main() {
  fstream fin;
  fin.open("synonyms.txt");
  if (!fin.is_open()) {
    exit(EXIT_FAILURE);
    return 1;
  }

  Synonyms dict;

  int n;
  fin >> n;
  for (int i = 0; i < n; ++i) {
    string command;
    fin >> command;
    if (command == "ADD") {
      string word1;
      string word2;

      fin >> word1 >> word2;
      dict.add(word1, word2);
    } else if (command == "COUNT") {
      string word;
      fin >> word;
      int count = dict.count(word);
      cout << count << endl;
    } else if (command == "CHECK") {
      string word1;
      string word2;

      fin >> word1 >> word2;
      if (dict.check(word1, word2)) {
        cout << "YES" << endl;
      } else {
        cout << "NO" << endl;
      }
    }
  }

  return 0;
}