#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "test_runner.h"
#include "profile.h"
#include "learner.h"

using namespace std;

int main() {
  vector<string> words;
  generate_n(back_insert_iterator<vector<string>>(words), 10000, []{ return GetRandomString(5); });

  {
    LOG_DURATION("Learn by word (original)");

    Learner learner;
    for (const auto& word : words) {
      learner.Learn({ word });
    }
  }
  {
    LOG_DURATION("Learn by word (fast)");

    FastLearner learner;
    for (const auto& word : words) {
      learner.Learn({ word });
    }
  }

  {
    LOG_DURATION("Learn by words");

    Learner learner;
    learner.Learn(words);
  }
  {
    LOG_DURATION("Learn by words (fast)");

    FastLearner learner;
    learner.Learn(words);
  }

  {
    Learner learner;
    learner.Learn(words);

    LOG_DURATION("Known words (original)");
    cout << learner.KnownWords().size() << '\n';
  }
  {
    FastLearner learner;
    learner.Learn(words);

    LOG_DURATION("Known words (fast)");
    cout << learner.KnownWords().size() << '\n';
  }

  return 0;
}