#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <exception>
#include <vector>
#include <iomanip>

using namespace std;

class Figure {
public:
  virtual string Name() const = 0;
  virtual double Perimeter() const = 0;
  virtual double Area() const = 0;
};

class Triangle : public Figure {
private:
  double a, b, c;
public:
  Triangle(double _a, double _b, double _c): a(_a), b(_b), c(_c) {};
  string Name() const override { return "TRIANGLE"; };
  double Perimeter() const override { return a + b + c; };
  double Area() const override { return 0; }; // TODO: implement
};

class Rect : public Figure {
private:
  double width;
  double height;
public:
  Rect(double w, double h): width(w), height(h) {};
  string Name() const override { return "RECT"; };
  double Perimeter() const override { return (width + height) * 2; };
  double Area() const override { return width * height; };
};

static const double PI = 3.14;

class Circle : public Figure {
private:
  double r;
public:
  Circle(double _r): r(_r) {};
  string Name() const override { return "CIRCLE"; };
  double Perimeter() const override { return 2 * PI * r; };
  double Area() const override { return r * r * PI; };
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
  string figure;
  is >> figure;
  if (figure == "RECT") {
    int width, height;
    is >> width >> height;
    return make_shared<Rect>(width, height);
  } else if (figure == "TRIANGLE") {
    int a, b, c;
    is >> a >> b >> c;
    return make_shared<Triangle>(a, b, c);
  } else if (figure == "CIRCLE") {
    int r;
    is >> r;
    return make_shared<Circle>(r);
  } else {
    throw invalid_argument("unknown figure");
  }
}

int main() {
  fstream fin("figures.txt");

  vector<shared_ptr<Figure>> figures;
  for (string line; getline(fin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}