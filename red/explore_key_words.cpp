#include "test_runner.h"
#include "profile.h"

#include <map>
#include <iostream>
#include <functional>
#include <future>
#include <string>
using namespace std;

/*
Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  const size_t max_batch_size = 5000;
  vector<string> batch;
  batch.reserve(max_batch_size);
  vector<future<Stats>> futures;

  for (string line; getline(input, line); ) {
    batch.push_back(move(line));

    if (batch.size() >= max_batch_size) {
      futures.push_back(async(ExploreBatch), ref(key_words), move(batch));
      batch.reserve(max_batch_size);
    }
  }
}

 */

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
    for (const auto& [word, frequences] : other.word_frequences) {
      word_frequences[word] += frequences;
    }
  }

  friend ostream& operator<<(ostream& out, const Stats& other) {
    for (const auto& [word, frequences] : other.word_frequences) {
      out << word << ": " << frequences << '\n';
    }
    return out;
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
  cout << "Explore line: " << line << '\n';
  Stats result;

  stringstream is(line);
  for (string str; getline(is, str, ' '); ) {
    if (key_words.count(str)) {
      result.word_frequences[str] += 1;
    }
  }

  cout << "Got result:" << '\n';
  cout << result;

  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  vector<future<Stats>> futures;

  for (string str; getline(input, str, '\n');) {
    futures.push_back(async(ExploreLine, ref(key_words), str));
  }

  Stats result;
  for (auto& f : futures) {
    result += f.get();
  }

  return result;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
