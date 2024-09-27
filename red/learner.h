#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Learner {
 private:
  vector<string> dict;

 public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (find(dict.begin(), dict.end(), word) == dict.end()) {
        ++newWords;
        dict.push_back(word);
      }
    }
    return newWords;
  }

  vector<string> KnownWords() {
    sort(dict.begin(), dict.end());
    dict.erase(unique(dict.begin(), dict.end()), dict.end());
    return dict;
  }
};

class FastLearner : public Learner {
private:
  set<string> dict;
public:
  int Learn(const vector<string>& words) {
    size_t prevSize = dict.size();
    dict.insert(words.begin(), words.end());
    return dict.size() - prevSize;
  }

  vector<string> KnownWords() {
    return {dict.begin(), dict.end()};
  }
};
