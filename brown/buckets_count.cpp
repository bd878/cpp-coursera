#include <unordered_map>
#include <tuple>
#include <iostream>
#include <functional>

using namespace std;

struct DecartPoint {
  int x;
  int y;

  bool operator==(const DecartPoint& other) const {
    return pair(x, y) == pair(other.x, other.y);
  }
};

struct DecartPointHash {
  int coef = 73;
  hash<int> int_hash;

  size_t operator()(const DecartPoint& point) const {
    return coef * int_hash(point.x) + int_hash(point.y);
  }
};

ostream& operator<<(ostream& out, const DecartPoint& point) {
  out << "(" << point.x << ", " << point.y << ")" << '\n';
  return out;
}

struct PolarPoint {
  double length;
  double r_angle;
};

ostream& operator<<(ostream& out, const PolarPoint& point) {
  out << "[" << point.r_angle << ", " << point.length << "]" << '\n';
  return out;
}

int main() {
  unordered_map<DecartPoint, PolarPoint, DecartPointHash> decart_to_point;
  decart_to_point.insert({{5, 3}, {5.8, 0.54}});
  decart_to_point.insert({{6, 10}, {11.6, 1.03}});

  cout << "Size: " << decart_to_point.size() << '\n'
    << "Buckets: " << decart_to_point.bucket_count() << endl;

  return 0;
}