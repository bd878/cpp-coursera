#pragma once

#include "http_request.h"

#include <string_view>
#include <vector>
#include <map>
using namespace std;

class Stats {
private:
  map<string_view, int> method_stats{
    {"GET", 0},
    {"PUT", 0},
    {"POST", 0},
    {"DELETE", 0},
    {"UNKNOWN", 0},
  };
  map<string_view, int> uri_stats{
    {"/", 0},
    {"/order", 0},
    {"/product", 0},
    {"/basket", 0},
    {"/help", 0},
    {"unknown", 0},
  };
public:
  void AddMethod(string_view method) {
    if (method_stats.count(method)) {
      method_stats[method] += 1;
    } else {
      method_stats["UNKNOWN"] += 1;
    }
  }
  void AddUri(string_view uri) {
    if (uri_stats.count(uri)) {
      uri_stats[uri] += 1;
    } else {
      uri_stats["unknown"] += 1;
    }
  }
  const map<string_view, int>& GetMethodStats() const { return method_stats; };
  const map<string_view, int>& GetUriStats() const { return uri_stats; };
};

HttpRequest ParseRequest(string_view line) {
  HttpRequest result;

  size_t pos = line.find_first_not_of(' ');
  const size_t pos_end = line.npos;

  for (string_view* field : {&result.method, &result.uri, &result.protocol}) {
    size_t found = line.find(' ', pos);

    if (found == pos_end) {
      *field = line.substr(pos);
    } else {
      *field = line.substr(pos, found - pos);
      pos = found + 1;
    }
  }

  return result;
}
