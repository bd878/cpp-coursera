#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <deque>
#include "test_runner.h"
using namespace std;

class Editor {
private:
  deque<char> text;
  deque<char> buffer;
  size_t pos;

  using TextIt = deque<char>::const_iterator;

  pair<TextIt, TextIt> Slice(size_t tokens = 1) const {
    size_t end_pos = min(text.size(), pos + tokens);

    auto it = text.begin() + pos;
    auto end_it = text.begin() + end_pos;

    return make_pair(it, end_it);
  }
public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor() : pos(0) {};
  void Left() {
    pos = static_cast<size_t>(max(0, int(pos) - 1));
  }
  void Right() {
    pos = min(text.size(), pos + 1);
  }
  void Insert(char token) {
    text.insert(text.begin() + pos, token);
    pos += 1;
  }
  void Cut(size_t tokens = 1) {
    const auto& [it, end_it] = Slice(tokens);
    buffer.assign(it, end_it);
    text.erase(it, end_it);
  }
  void Copy(size_t tokens = 1) {
    const auto& [it, end_it] = Slice(tokens);
    buffer.assign(it, end_it);
  }
  void Paste() {
    text.insert(text.begin() + pos, buffer.begin(), buffer.end());
    pos += buffer.size();
  }
  size_t Pos() {
    return pos;
  }
  string GetText() const {
    string result;
    copy(text.begin(), text.end(), back_inserter(result));
    return result;
  }
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

int main1() {
  Editor editor;
  string text = "abc";

  TypeText(editor, text);
  cout << editor.GetText() << '\n';
  cout << "Pos: " << editor.Pos() << '\n';
  for(size_t i = 0; i < text.size(); ++i) {
    editor.Left();
  }
  cout << "Pos: " << editor.Pos() << '\n';

  return 0;
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}