#include "test_runner.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Translator {
private:
  set<string> strings;
  map<string_view, string_view> forward;
  map<string_view, string_view> backward;
public:
  void Add(string_view source, string_view target) {
    const auto& source_str = strings.insert(string(source));
    const auto& target_str = strings.insert(string(target));

    forward[*(source_str.first)] = *(target_str.first);
    backward[*(target_str.first)] = *(source_str.first);
  }

  string_view TranslateForward(string_view source) const {
    if (forward.count(source)) {
      return forward.at(source);
    } else {
      return "";
    }
  }
  string_view TranslateBackward(string_view target) const {
    if (backward.count(target)) {
      return backward.at(target);
    } else {
      return "";
    }
  }
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
