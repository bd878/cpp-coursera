#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>

using namespace std;

int main() {
  fstream fin{"braces.txt"};

  int first = 0;
  size_t count = 0;
  fin >> first >> count;

  deque<string> ops;
  ops.push_back(to_string(first));
 
  string op;
  fin.ignore(1);
  while (getline(fin, op)) {
    ops.push_back(op);
  }

  string head, tail;
  bool is_braces = false;
  for (string op : ops) {
    head = op;

    if (tail.empty()) {
      tail = head;
    } else {
      if (is_braces) {
        tail = "(" + tail + ") " + head;
      } else {
        tail += ' ' + head;
      }
    }

    switch (op[0]) {
      case '*':
      case '/':
        is_braces = false;
        break;
      case '+':
      case '-':
        is_braces = true;
        break;
      default:
        break;
    }
  }

  cout << tail << endl;

  return 0;
}