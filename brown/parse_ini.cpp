#include <sstream>
#include <iostream>
#include <utility>

using namespace std;

pair<string_view, string_view> Split(string_view line, char by) {
  size_t pos = line.find(by);
  string_view left = line.substr(0, pos);

  if (pos < line.size() && pos + 1 < line.size()) {
    return {left, line.substr(pos + 1)};
  } else {
    return {left, string_view()};
  }
}

int main() {
  istringstream input(
R"([july]
food=2500
sport=12000
travel=23400
clothes=5200

[august]
food=3250
sport=10000
travel=0
clothes=8300
jewelery=25000
)"
  );

  for (string section; input >> section; ) {
    string_view section_view = section;
    section_view.remove_prefix(1);
    section_view.remove_suffix(1);

    cout << section_view << '\n';
    cout << "===" << endl;

    for (char c; input >> c;) {
      input.putback(c);

      if (c == '[') {
        break;
      }

      string key_value;
      input >> key_value;

      string_view kv_view = key_value;
      auto [key, value] = Split(kv_view, '=');
      cout << key << ": " << value << '\n';
    }

    cout << '\n';
  }

  return 0;
}