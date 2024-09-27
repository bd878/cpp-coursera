#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class FunctionPart {
private:
  char operation;
  int value;
public:
  FunctionPart(char op, int v): operation{op}, value{v} {};
  double Apply(double v) const;
  void Invert();
};

double FunctionPart::Apply(double v) const {
  if (operation == '+') {
    return v + value;
  } else if (operation == '-') {
    return v - value;
  } else if (operation == '*') {
    return v * value;
  } else if (operation == '/') {
    return v / value;
  } else {
    cout << "Unknown operation " << operation << endl;
    return 0.0;
  }
}

void FunctionPart::Invert() {
  if (operation == '+') {
    operation = '-';
  } else if (operation == '-') {
    operation = '+';
  } else if (operation == '*') {
    operation = '/';
  } else if (operation == '/') {
    operation = '*';
  } else {
    cout << "Can not invert unknown operation " << operation << endl;
  }
}

class Function {
private:
  vector<FunctionPart> parts;
public:
  void AddPart(char operation, int value);
  double Apply(double value) const;
  void Invert();
};

void Function::AddPart(char operation, int value) {
  parts.push_back({ operation, value });
}

double Function::Apply(double value) const {
  for (const auto& part : parts) {
    value = part.Apply(value);
  }
  return value;
}

void Function::Invert() {
  for (auto& part : parts) {
    part.Invert();
  }
  reverse(begin(parts), end(parts));
}
