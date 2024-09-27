#include <memory>
#include <string>
#include <iostream>

#include "profile.h"
#include "test_runner.h"

using namespace std;

struct Book {
  Book(): author(""), name(""), count(0) {};
  Book(const string& a, const string& n, int c):
    author(a), name(n), count(c) {};

  string author;
  string name;
  int count;
};

int main() {
  {
    LOG_DURATION("SharedStructs");
    vector<shared_ptr<Book>> books(86400, make_shared<Book>());

    // for (const auto& book : books) {
    //   cout << book->author << ' '
    //     << book->name << ' '
    //     << book->count << '\n';
    // }
  }

  return 0;
}
