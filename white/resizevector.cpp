#include <vector>
#include <iostream>

using namespace std;

int main() {
  vector<vector<string>> tasks{31};
  cout << tasks.size() << endl;

  tasks.resize(28);
  cout << tasks.size() << endl;

  tasks.resize(31);
  cout << tasks.size() << endl;

  return 0;
}