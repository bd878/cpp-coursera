#include <algorithm>
#include <utility>
#include <functional>
#include <iterator>
#include <sstream>
#include <iostream>
#include <future>
#include <mutex>
#include <string_view>

#include "profile.h"
#include "parse.h"
#include "paginator.h"
#include "test_runner.h"

using namespace std;

vector<string> SplitIntoWords1(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

vector<string_view> SplitIntoWords2(const string& line) {
  return SplitBy(line, ' ');
}

static const size_t WORDS_COUNT = 10e2;
static const size_t LINES_COUNT = 10e2;

string GenerateRandomLine() {
  vector<string> words;
  words.reserve(WORDS_COUNT);
  generate_n(back_inserter(words), WORDS_COUNT, []{ return GetRandomString(10); });
  return Join(' ', words);
}

template <typename C>
void FillWithLines(C& cont) {
  generate(cont.begin(), cont.end(), GenerateRandomLine);
}

vector<string> GenerateLines() {
  vector<string> lines(LINES_COUNT);

  LOG_DURATION("Generating lines in");
  vector<future<void>> futures;
  for (auto page : Paginate(lines, LINES_COUNT / 4)) {
    futures.push_back(async([page]{ FillWithLines(page); }));
  }

  return lines;
}

void ProfileSplitIntoWords(const vector<string>& lines) {
  size_t size1, size2;
  {
    LOG_DURATION("SplitIntoWords1");
    for (const auto& line : lines) {
      const auto& result = SplitIntoWords1(line);
      size1 = result.size();
    }
  }
  {
    LOG_DURATION("SplitIntoWords2");
    for (const auto& line : lines) {
      const auto& result = SplitIntoWords2(line);
      size2 = result.size();
    }
  }

  ASSERT(size1 == size2);
}

void ProfileParseStream(const vector<string>& lines) {
  istringstream is(Join('\n', lines));
  {
    LOG_DURATION("Sync read and parse");
    for (string line; getline(is, line); ) {
      SplitIntoWords2(line);
    }
  }

  istringstream other_is(Join('\n', lines));
  {
    LOG_DURATION("Parallel read and parse");
    vector<string> query_lines;
    for (string line; getline(other_is, line); ) {
      query_lines.push_back(move(line));
    }

    vector<future<void>> futures;
    for (auto page : Paginate(query_lines, query_lines.size() / 4)) {
      futures.push_back(async([page]{
        for (auto& line : page) {
          SplitIntoWords2(line);
        }
      }));
    }
  }
}

int main() {
  vector<string> lines = GenerateLines();

  ProfileSplitIntoWords(lines);
  ProfileParseStream(lines);

  return 0;
}
