#include <future>
#include <functional>
#include <sstream>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

struct Stats {
  string line;
  map<string, int> words;

  void operator += (const Stats& other) {
    for (const auto& [word, count] : other.words) {
      words[word] += count;
    }
  }

  friend ostream& operator<<(ostream& out, const Stats& other) {
    cout << "Stats of line: " << other.line << '\n';
    for (const auto& [word, count] : other.words) {
      out << word << ": " << count << '\n';
    }
    return out;
  }
};

Stats LineStats(const string& line) {
  Stats result{line};

  stringstream is(line);
  for (string str; getline(is, str, ' '); ) {
    result.words[str] += 1;
  }

  return result;
}

Stats CountWords(istream& input) {
  vector<future<Stats>> futures;

  for (string str; getline(input, str); ) {
    cout << "Processing line: " << str << '\n';
    futures.push_back(async(LineStats, str));
  }

  Stats result;
  for (auto& f : futures) {
    Stats temp(f.get());
    cout << temp << '\n';
    result += temp;
  }

  return result;
}

int main() {
  stringstream ss;
  ss << "I am travelling down the river\n";
  ss << "How much is the fish\n";
  ss << "Chicken egg and chips\n";

  const auto stat = CountWords(ss);
  cout << stat;

  return 0;
}