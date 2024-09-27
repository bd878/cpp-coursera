#include <cstdlib>
#include <iostream>

using namespace std;

void UpdateIfGreater(int a, int* b) {
  if (a > *b) {
    *b = a;
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " number number" << '\n';
    return 1;
  }

  int a = atoi(argv[1]);
  int b = atoi(argv[2]);

  cout << "a: " << a << "; b: " << b << '\n';
  UpdateIfGreater(a, &b);
  cout << "a: " << a << "; b: " << b << '\n';

  return 0;
}