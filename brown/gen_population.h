#pragma once

#include <string>
#include <tuple>
#include <array>
#include <random>
#include <utility>

stringstream GenPopulation() {
  using namespace std;

  stringstream ss(R"(11
Ivan 25 1000 M
Olga 30 623 W
Sergey 24 825 M
Maria 42 1254 W
Mikhail 15 215 M
Oleg 18 230 M
Denis 53 8965 M
Maxim 37 9050 M
Ivan 47 19050 M
Ivan 17 50 M
Olga 23 550 W
AGE 18
AGE 25
WEALTHY 5
POPULAR_NAME M
  )");

  return move(ss);
}

stringstream GenPopulation2() {
  using namespace std;

  const static int PEOPLE_COUNT = 10e5;
  const static int N = 10;
  const array<pair<string, char>, N> Names{
    make_pair("Ivan", 'M'),
    make_pair("Olga", 'F'),
    make_pair("Yuri", 'M'),
    make_pair("Igor", 'M'),
    make_pair("Denis", 'M'),
    make_pair("Maxim", 'M'),
    make_pair("Pavel", 'M'),
    make_pair("Xenia", 'F'),
    make_pair("Dmitri", 'M'),
    make_pair("Alex", 'M')
  };

  default_random_engine RandEng;
  uniform_int_distribution<int> NameDist{0, N - 1};
  uniform_int_distribution<int> AgeDist{10, 100};
  uniform_int_distribution<int> IncomeDist{1, 99999};

  stringstream ss;
  ss << PEOPLE_COUNT << '\n';
  for (size_t i = 0; i < PEOPLE_COUNT; ++i) {
    pair<string, char> ng = Names[NameDist(RandEng)];
    ss << ng.first << ' '
      << AgeDist(RandEng) << ' ' << IncomeDist(RandEng)
      << ng.second << '\n';
  }
  ss << R"(WEALTHY 100
AGE 18
POPULAR_NAME F
AGE 25
WEALTHY 5
POPULAR_NAME M
  )";

  return move(ss);
};
