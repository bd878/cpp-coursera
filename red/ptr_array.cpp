#include <iostream>

using namespace std;

int main() {
  size_t count = 5;
  int* arr = new int[count];
  for (size_t i = 0; i < count; i++) {
    arr[i] = i;
  }
  cout << *(arr + 3) << '\n';
  return 0;
}