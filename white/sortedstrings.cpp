#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class SortedStrings {
private:
  vector<string> strings;
  void SortStrings();
public:
  void AddString(const string& s);
  vector<string> GetSortedStrings() const;
};

void SortedStrings::SortStrings() {
  sort(begin(strings), end(strings));
}

void SortedStrings::AddString(const string& s) {
  strings.push_back(s);
  SortStrings();
}

vector<string> SortedStrings::GetSortedStrings() const {
  return strings;
}

void PrintSortedStrings(SortedStrings& strings) {
  for (const string& s : strings.GetSortedStrings()) {
    cout << s << " ";
  }
  cout << endl;
}

int main() {
  SortedStrings strings;
  
  strings.AddString("first");
  strings.AddString("third");
  strings.AddString("second");
  PrintSortedStrings(strings);
  
  strings.AddString("second");
  PrintSortedStrings(strings);
  
  return 0;
}
