#include <iostream>
#include <fstream>
#include <cstdint>

using namespace std;

int main() {
  fstream fin("blockweight.txt");

  uint32_t n;
  uint r;
  uint16_t w, h, d;
  uint32_t sum = 0;

  fin >> n >> r;
  cout << n << ' ' << r << '\n';
  for (; n > 0; --n) {
    fin >> w >> h >> d;
    cout << w << ' ' << h << ' ' << d << '\n';
    sum += (w * h * d * r);
  }

  cout << sum << endl;
  return 0;
}