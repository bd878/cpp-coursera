#include <string>
#include <map>
#include <iostream>
#include <string_view>

using namespace std;

string_view GetString() {
  string str = "abc";
  return str;
}

int main() {
  string_view str_view = GetString();

  cout << "str_view out of block: " << str_view << '\n';

  string a1 = "abc";
  string a2 = "abc";
  string_view a1_view = a1;
  string_view a2_view = a2;

  cout << "a1 == a2: " << (a1 == a2) << '\n';
  cout << "a1_view == a2_view: " << (a1_view == a2_view) << '\n';
  cout << "&a1 == &a2: " << (&a1 == &a2) << '\n';

  string a1_copy{a1_view};

  a1[0] = 'b';
  cout << "changed a1: " << a1 << '\n';
  cout << "changed a1_view: " << a1_view << '\n';
  cout << "a1_copy: " << a1_copy << '\n';

  map<string_view, string_view> views;
  views[a1] = a2;
  cout << "views[a1]: " << views[a1] << '\n';

  return 0;
}