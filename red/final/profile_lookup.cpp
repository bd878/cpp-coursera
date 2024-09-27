#include <random>
#include <functional>
#include <future>
#include <iterator>
#include <iostream>
#include <map>
#include <list>
#include <algorithm>
#include <vector>

#include "profile.h"
#include "paginator.h"
#include "concurrent_map.h"

#include "test_runner.h"

using namespace std;

vector<int> GenWords(size_t words_count) {
  vector<int> words(words_count);
  iota(words.begin(), words.end(), -words_count / 2);
  return words;
}

map<int, list<size_t>> GenLookupTable(const vector<int>& words, size_t docs_count) {
  random_device rd;
  mt19937 gen{rd()};
  uniform_int_distribution<> randint(0, words.size() - 1);

  map<int, list<size_t>> result;
  for (size_t doc_id = 0; doc_id < docs_count; ++doc_id) {
    int word = words[randint(gen)];
    result[word].push_back(doc_id);
  }

  return result;
}

vector<int> GenSentence(const vector<int>& words, size_t length) {
  random_device rd;
  mt19937 gen{rd()};
  uniform_int_distribution<> randint(0, words.size() - 1);

  vector<int> result(length);
  generate(result.begin(), result.end(), [&words, &gen, &randint]{ return words[randint(gen)]; });

  return result;
}

vector<vector<int>> GenSentences(const vector<int>& words, size_t sentences_count) {
  vector<vector<int>> result;
  result.reserve(sentences_count);

  size_t sentence_length = words.size() / 5;
  for (size_t i = 0; i < sentences_count; ++i) {
    result.push_back(GenSentence(words, sentence_length));
  }

  return result;
}

size_t CountHitcount(const map<size_t, int>& hitcount_table) {
  return accumulate(hitcount_table.begin(), hitcount_table.end(), 0, [](size_t result, const auto& doc_hits){
    return result + doc_hits.second;
  });
}

int main() {
  vector<int> words = GenWords(100);
  map<int, list<size_t>> lookup_table = GenLookupTable(words, 10e6);
  vector<int> sentence = GenSentence(words, 10);
  size_t hitcount1, hitcount2;
  {
    LOG_DURATION("Sync lookup");
    map<size_t, int> result;
    for (auto word : sentence) {
      const auto& docs = lookup_table.find(word)->second;
      for (const size_t doc_id : docs) {
        result[doc_id]++;
      }
    }

    hitcount1 = CountHitcount(result);
    cout << "hitcount1: " << hitcount1 << '\n';
  }
  {
    LOG_DURATION("Parallel lookup");
    const size_t threads_count = 3;

    ConcurrentMap<size_t, int> result(10);
    vector<future<void>> futures;
    for (auto page : Paginate(sentence, sentence.size() / threads_count)) {
      futures.push_back(async([page, &lookup_table, &result]{
        for (auto word : page) {
          const auto& docs = lookup_table.find(word)->second;
          for (const size_t doc_id : docs) {
            result[doc_id].ref_to_value++;
          }
        }
      }));
    }

    for (auto& f : futures) {
      f.get();
    }

    // hitcount2 = CountHitcount(result.BuildOrdinaryMap());
    // cout << "hitcount2: " << hitcount2 << '\n';
  }

  // ASSERT(hitcount1 == hitcount2);

  return 0;
}
