#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class ReversibleString {
private:
  string str;
public:
  ReversibleString(string s = ""): str{s} {};
  void Reverse();
  string ToString() const;
};

void ReversibleString::Reverse() {
  reverse(begin(str), end(str));
}

string ReversibleString::ToString() const {
  return str;
}

int main() {
  ReversibleString s("live");
  s.Reverse();
  cout << s.ToString() << endl;
  
  s.Reverse();
  const ReversibleString& s_ref = s;
  string tmp = s_ref.ToString();
  cout << tmp << endl;
  
  ReversibleString empty;
  cout << '"' << empty.ToString() << '"' << endl;
  
  return 0;
}