#include <string>

using namespace std;

struct Specialization {
  string name;
  explicit Specialization(const string& n): name{n} {};
};

struct Course {
  string name;
  explicit Course(const string& n): name{n} {};
};

struct Week {
  string name;
  explicit Week(const string& n): name{n} {};
};

struct LectureTitle {
  Specialization specialization;
  Course course;
  Week week;
  explicit LectureTitle(
    const Specialization& spec,
    const Course& c,
    const Week& w
  ): specialization{spec}, course{c}, week{w} {};
};
