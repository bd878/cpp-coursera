#include <iostream>
#include <sstream>

#include "http_request.h"
#include "stats.h"

using namespace std;

int main() {
  const string input =
    R"(GET / HTTP/1.1
    POST /order HTTP/1.1
    HEAD / HTTP/1.1)";

  istringstream is(input);

  for (string line; getline(is, line); ) {
    const HttpRequest req = ParseRequest(line);
    cout << req.method << '\n'
      << req.uri << '\n'
      << req.protocol << '\n';
  }

  return 0;
}