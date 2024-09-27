#pragma once

#include <string>
#include <memory>

#include "date.h"

using namespace std;

enum class LogicalOperation {
  Or,
  And,
};

enum class Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual,
};

struct Node {
  virtual bool Evaluate(const Date&, const string&) const = 0;
};

class DateComparisonNode : public Node {
private:
  Comparison cmp_;
  Date date_;
public:
  DateComparisonNode(Comparison c, const Date& d): cmp_{c}, date_{d} {};
  bool Evaluate(const Date&, const string&) const override;
};

class EventComparisonNode : public Node {
private:
  Comparison cmp_;
  string event_;
public:
  EventComparisonNode(Comparison c, const string& str): cmp_{c}, event_{str} {};
  bool Evaluate(const Date&, const string&) const override;
};

class LogicalOperationNode : public Node {
private:
  shared_ptr<Node> left_;
  shared_ptr<Node> right_;
  LogicalOperation operation_;
public:
  LogicalOperationNode(LogicalOperation op, shared_ptr<Node> l, shared_ptr<Node> r)
    : operation_{op}, left_{l}, right_{r} {};
  bool Evaluate(const Date&, const string&) const override;
};

struct EmptyNode : public Node {
  bool Evaluate(const Date&, const string&) const override {
    return false;
  }
};