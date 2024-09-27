#include <unordered_map>
#include <iostream>

using namespace std;

int main() {
  unordered_map<int, string> banknotes({
    {1000, "thousand"},
    {2000, "two thousands"},
    {5000, "five thousands"}
  });

  auto found = banknotes.find(1000);
  cout << found.second << endl;

  return 0;
}