#pragma once

#include <utility>
#include <memory>
#include <string>

// Базовый класс арифметического выражения
class Expression {
public:
  virtual ~Expression() = default;

  // Вычисляет значение выражения
  virtual int Evaluate() const = 0;

  // Форматирует выражение как строку
  // Каждый узел берётся в скобки, независимо от приоритета
  virtual std::string ToString() const = 0;
};

using ExpressionPtr = std::unique_ptr<Expression>;

class Num : public Expression {
private:
  int value;
public:
  explicit Num(int v) : value(v) {};

  int Evaluate() const {
    return value;
  }

  std::string ToString() const {
    return std::to_string(value);
  }
};

class Plus : public Expression {
private:
  ExpressionPtr left;
  ExpressionPtr right;
public:
  explicit Plus(ExpressionPtr l, ExpressionPtr r)
    : left(std::move(l)), right(std::move(r)) {}

  int Evaluate() const {
    return left->Evaluate() + right->Evaluate();
  }

  std::string ToString() const {
    return "(" + left->ToString() + ")+(" + right->ToString() + ")";
  }
};

class Multiply : public Expression {
private:
  ExpressionPtr left;
  ExpressionPtr right;
public:
  explicit Multiply(ExpressionPtr l, ExpressionPtr r)
    : left(std::move(l)), right(std::move(r)) {}

  int Evaluate() const {
    return left->Evaluate() * right->Evaluate();
  }

  std::string ToString() const {
    return "(" + left->ToString() + ")*(" + right->ToString() + ")";
  }
};

// Функции для формирования выражения
ExpressionPtr Value(int value);
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right);
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right);

ExpressionPtr Value(int value) {
  return std::make_unique<Num>(value);
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
  return std::make_unique<Plus>(std::move(left), std::move(right));
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
  return std::make_unique<Multiply>(std::move(left), std::move(right));
}