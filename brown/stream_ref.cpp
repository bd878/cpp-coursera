#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Logger {
  ostream& out;

  Logger(ostream& os) : out(os) {}

  void Log(string message) {
    out << "Logged!\n";
    out << message;
  }
};

int main() {
  Logger logger(cout);

  logger.Log("Hello, world!\n");

  return 0;
}