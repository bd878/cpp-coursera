#pragma once

#include <fstream>
#include <iostream>

#include "profile.h"
#include "test_runner.h"

using namespace std;

void genReadAndCheer(
  int max_reader = 10e4,
  int max_queries = 10e3,
  int max_pages = 10e2,
  string file_name = "readers.txt"
) {
  LOG_DURATION("genReadAndCheer");

  ofstream fout(file_name);
  vector<int> pages(max_pages, 1);

  auto cheerOrRead([max_reader]{
    return ((GetRandomInt(0, max_reader) % 2) ? "READ" : "CHEER");
  });

  fout << max_queries << '\n';
  for (int i = 0; i < max_queries; ++i) {
    if (cheerOrRead() == "READ") {
      int reader = GetRandomInt(0, max_reader);
      int& page = pages[reader % max_pages];

      fout << "READ " << reader << ' ' << (page++) << '\n';
    } else {
      fout << "CHEER " << GetRandomInt(0, max_reader) << '\n';
    }
  }
}

void genRead(
  int max_reader = 10e4,
  int max_queries = 10e3,
  int max_pages = 10e2,
  string file_name = "readers.txt"
) {
  LOG_DURATION("genRead");

  ofstream fout(file_name);
  vector<int> pages(max_pages, 1);

  fout << max_queries << '\n';
  for (int i = 0; i < max_queries; ++i) {
    int reader = GetRandomInt(0, max_reader);
    int& page = pages[reader % max_pages];

    fout << "READ " << reader << ' ' << (page++) << '\n';
  }
}
