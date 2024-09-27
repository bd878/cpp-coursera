#include <vector>
#include <iterator>
#include <utility>
#include <iostream>

using namespace std;

struct Token {
  int value;

  Token(int v) : value(v) {
    cout << "Token constructor" << '\n';
  }
  Token(Token&& other) {
    cout << "Move token" << '\n';
    swap(other.value, value);
  };
  Token(const Token& other) {
    cout << "Token copy constructor" << '\n';
    value = other.value;
  }
  void operator=(const Token& other) {
    cout << "Token copy assignment" << '\n';
    value = other.value;
  }
};

ostream& operator<<(ostream& out, const Token& t) {
  out << t.value;
  return out;
}

template <typename T>
void PrintVector(const vector<T>& v) {
  copy(v.begin(), v.end(), ostream_iterator<T>(cout, " "));
  cout << '\n';
}

int main() {
  vector<Token> tokens;
  Token value{1};
  Token* value_ptr = &value;

  cout << "Value before: " << value << '\n';
  cout << "Value_ptr before: " << *value_ptr << '\n';
  tokens.push_back(move(value));
  cout << "Value after: " << value << '\n';
  cout << "Value_ptr after: " << *value_ptr << '\n';
  value_ptr->value = 123;
  cout << "Value after ptr assignment: " << value << '\n';
  cout << "Value_ptr after ptr assignment: " << *value_ptr << '\n';

  return 0;
}