#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
private:
  int rows;
  int columns;
  vector<vector<int>> table;
public:
  Matrix();
  Matrix(int num_rows, int num_columns);
  void Reset(int num_rows, int num_columns);
  int At(int row, int column) const;
  int& At(int row, int column);
  int GetNumRows() const { return rows; };
  int GetNumColumns() const { return columns; };
  friend istream& operator>>(istream&, Matrix&);
  friend ostream& operator<<(ostream&, const Matrix&);
  bool operator==(const Matrix&);
  Matrix operator+(const Matrix&);
};

Matrix::Matrix() {
  rows = 0;
  columns = 0;
}

Matrix::Matrix(int num_rows, int num_columns) {
  Reset(num_rows, num_columns);
}

void Matrix::Reset(int num_rows, int num_columns) {
  if (num_rows < 0)
    throw out_of_range("rows must be >= 0");

  if (num_columns < 0)
    throw out_of_range("columns must be >= 0");

  if (num_rows == 0 || num_columns == 0)
    num_rows = num_columns = 0;

  rows = num_rows;
  columns = num_columns;
  table.assign(num_rows, vector<int>(num_columns));
}

int& Matrix::At(int row, int column) {
  return table.at(row).at(column);
}

int Matrix::At(int row, int column) const {
  return table.at(row).at(column);
}

istream& operator>>(istream& is, Matrix& m) {
  int r, c;
  is >> r >> c;

  m.Reset(r, c);

  for (int i = 0; i < r; ++i)
    for (int j = 0; j < c; ++j)
      is >> m.At(i, j);

  return is;
}

ostream& operator<<(ostream& os, const Matrix& m) {
  os << m.GetNumRows() << ' ' << m.GetNumColumns();
  for (const auto& table_row : m.table) {
    os << '\n';
    for (const int value : table_row)
      os << value << ' ';
  }

  return os;
}

bool Matrix::operator==(const Matrix& m) {
  if (rows != m.GetNumRows())
    return false;

  if (columns != m.GetNumColumns())
    return false;

  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < columns; ++j)
      if (this->At(i, j) != m.At(i, j))
        return false;

  return true;
}

Matrix Matrix::operator+(const Matrix& m) {
  if (rows != m.GetNumRows())
    throw invalid_argument("mismatched number of rows");

  if (columns != m.GetNumColumns())
    throw invalid_argument("mismatched number of columns");

  Matrix result(rows, columns);
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < columns; ++j)
      result.At(i, j) = this->At(i, j) + m.At(i, j);

  return result;
}

int main() {
  fstream fin("matrix.txt");

  Matrix one;
  Matrix two;

  cin >> one >> two;
  cout << (one + two) << endl;
  return 0;
}
