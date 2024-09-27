#include <vector>
#include <random>
#include <iostream>
#include <utility>
#include <tuple>
#include <algorithm>
#include <fstream>

using namespace std;

void GenSportsman(
  int count = 10e4,
  int max_sportsman = 10e4
) {
  ofstream fout("sportsmen.txt");

  auto GetRandomSportsman([&max_sportsman](int except = 0) {
    static random_device rd;
    static mt19937 gen{rd()};
    static uniform_int_distribution<> randint(0, max_sportsman);

    int sportsmen = randint(gen);
    while (sportsmen == except) {
      sportsmen = randint(gen);
    }

    return sportsmen;
  });

  vector<pair<int, int>> sportsmen(max_sportsman);
  generate(sportsmen.begin(), sportsmen.end(), [first = 0, &GetRandomSportsman]() mutable {
    return make_pair(first++, GetRandomSportsman());
  });

  random_shuffle(sportsmen.begin(), sportsmen.end());

  fout << count << '\n';
  for (auto& [first, second] : sportsmen) {
    fout << first << ' ' << second << '\n';
  }
}
