#include <iostream>
#include <exception>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <cmath>
#include <numeric>

using namespace std;

class Rational {
private:
  int sign;
  int numerator;
  int denominator;
public:
  Rational(int num, int denom);
  int Numerator() const { return numerator * sign; };
  int Denominator() const { return denominator; };
  Rational& operator=(const Rational&);
  friend bool operator==(const Rational&, const Rational&);
  friend Rational operator*(const Rational&, const Rational&);
  friend Rational operator/(const Rational&, const Rational&);
  friend Rational operator-(const Rational&, const Rational&);
  friend Rational operator+(const Rational&, const Rational&);
  friend istream& operator>>(istream& is, Rational&);
  friend ostream& operator<<(ostream& os, const Rational&);
  friend bool operator>(const Rational&, const Rational&);
  friend bool operator<(const Rational&, const Rational&);
};

Rational::Rational(int num = 0, int denom = 1) {
  if (num < 0 && denom > 0) {
    sign = -1;
  } else if (num > 0 && denom < 0) {
    sign = -1;
  } else {
    sign = 1;
  }

  if (denom == 0) {
    throw invalid_argument("Invalid argument");
  }

  if (num == 0) {
    denom = 1;
  }

  unsigned int g = gcd(num, denom);
  numerator = abs(num) / g;
  denominator = abs(denom) / g;
}

bool operator==(const Rational& r1, const Rational& r2) {
  return r1.sign == r2.sign && r1.numerator == r2.numerator && r1.denominator == r2.denominator;
}

Rational operator*(const Rational& r1, const Rational& r2) {
  int denom = r1.Denominator() * r2.Denominator();
  int num = r1.Numerator() * r2.Numerator();
  return {num, denom};
}

Rational operator/(const Rational& r1, const Rational& r2) {
  if (r2.Numerator() == 0) {
    throw domain_error("Division by zero");
  }

  int denom = r1.Denominator() * r2.Numerator();
  int num = r1.Numerator() * r2.Denominator();
  return {num, denom};
}

Rational& Rational::operator=(const Rational& r) {
  if (this == &r) {
    return *this;
  }

  sign = r.sign;
  numerator = r.numerator;
  denominator = r.denominator;

  return *this; 
}

Rational operator-(const Rational& r1, const Rational& r2) {
  int denom = r1.Denominator() * r2.Denominator();
  int num = (r1.Numerator() * r2.Denominator()) - (r2.Numerator() * r1.Denominator());
  return {num, denom};
}

Rational operator+(const Rational& r1, const Rational& r2) {
  int denom = r1.Denominator() * r2.Denominator();
  int num = (r1.Numerator() * r2.Denominator()) + (r2.Numerator() * r1.Denominator());
  return {num, denom};
}

istream& operator>>(istream& is, Rational& r) {
  char op;
  int n, d;
  if (!(is >> n) || !(is >> op) || op != '/' || !(is >> d)) {
    n = r.Numerator();
    d = r.Denominator();
  }

  Rational new_r{n, d};
  r = new_r;

  return is;
}

ostream& operator<<(ostream& os, const Rational& r) {
  os << r.Numerator() << '/' << r.Denominator();
  return os;
}

bool operator<(const Rational& r1, const Rational& r2) {
  int num1 = r1.Numerator() * r2.Denominator();
  int num2 = r2.Numerator() * r1.Denominator();
  return num1 < num2;
}

bool operator>(const Rational& r1, const Rational& r2) {
  int num1 = r1.Numerator() * r2.Denominator();
  int num2 = r2.Numerator() * r1.Denominator();
  return num1 > num2;
}
