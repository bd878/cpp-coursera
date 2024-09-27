#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
  fstream fin;
  fin.open("./worrycount.txt");
  if (!fin.is_open()) {
    exit(EXIT_FAILURE);
    return 1;
  }

  vector<int> queue;

  auto print_worried([&queue]() {
    int worried_count = 0;
    for (int& person : queue)
      if (person == 1)
        worried_count++;

    cout << worried_count << endl;
  });

  int n;
  int op;
  fin >> n;
  string operand;
  for (int i = 0; i < n; ++i) {
    fin >> operand;
    if (operand == "WORRY") {
      fin >> op;
      queue[op - 1] = 1;
    } else if (operand == "QUIET") {
      fin >> op;
      queue[op - 1] = 0;
    } else if (operand == "COME") {
      fin >> op;
      queue.resize(queue.size() + op, 0);
    } else if (operand == "WORRY_COUNT") {
      print_worried();
    } else {
      cout << operand << " is undefined operand" << endl;
    }
  }
}
