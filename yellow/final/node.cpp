#include <exception>
#include <algorithm>

#include "node.h"

bool DateComparisonNode::Evaluate(const Date& date, const string& str) const {
  if (cmp_ == Comparison::Less) {
    return date < date_;
  } else if (cmp_ == Comparison::LessOrEqual) {
    return date <= date_;
  } else if (cmp_ == Comparison::Greater) {
    return date > date_;
  } else if (cmp_ == Comparison::GreaterOrEqual) {
    return date >= date_;
  } else if (cmp_ == Comparison::Equal) {
    return date_ == date;
  } else if (cmp_ == Comparison::NotEqual) {
    return date_ != date;
  }

  throw invalid_argument("unknown operation");
};

bool EventComparisonNode::Evaluate(const Date& date, const string& str) const {
  if (cmp_ == Comparison::Less) {
    return lexicographical_compare(event_.begin(), event_.end(), str.begin(), str.end());
  } else if (cmp_ == Comparison::LessOrEqual) {
    return (
      lexicographical_compare(event_.begin(), event_.end(), str.begin(), str.end()) ||
      event_ == str
    );
  } else if (cmp_ == Comparison::Greater) {
    return lexicographical_compare(str.begin(), str.end(), event_.begin(), event_.end());
  } else if (cmp_ == Comparison::GreaterOrEqual) {
    return (
      lexicographical_compare(str.begin(), str.end(), event_.begin(), event_.end()) ||
      event_ == str
    );
  } else if (cmp_ == Comparison::Equal) {
    return event_ == str;
  } else if (cmp_ == Comparison::NotEqual) {
    return event_ != str;
  }

  throw invalid_argument("unknown operation");
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& str) const {
  if (operation_ == LogicalOperation::Or) {
    return (left_->Evaluate(date, str) || right_->Evaluate(date, str));
  } else if (operation_ == LogicalOperation::And) {
    return (left_->Evaluate(date, str) && right_->Evaluate(date, str));
  }

  throw invalid_argument("unknown operation");
};
