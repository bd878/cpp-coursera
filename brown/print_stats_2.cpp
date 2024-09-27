#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <numeric>

// #include "profile.h"
// #include "gen_population.h"

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

private:
  Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
  return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
  string name;
  int age, income;
  bool is_male;
};

ostream& operator<<(ostream& out, const Person& p) {
  out << p.name << ' ' << p.age << ' ' << p.income << '\n';
  return out;
}

vector<Person> ReadPeople(istream& input) {
  int count;
  input >> count;

  vector<Person> result(count);
  for (Person& p : result) {
    char gender;
    input >> p.name >> p.age >> p.income >> gender;
    p.is_male = gender == 'M';
  }

  return result;
}

class DemographyStats {
private:
  using PeopleIt = typename vector<Person>::const_iterator;
  using SPeopleIt = typename vector<PeopleIt>::iterator;

  vector<PeopleIt> people;
  optional<string> male_popular_name;
  optional<string> female_popular_name;
  vector<PeopleIt> sorted_by_wealth;

  // or template <typename Iter>
  optional<string> FindMostPopularName(SPeopleIt first, SPeopleIt last) {
    if (first == last) {
      return nullopt;
    }

    sort(first, last, [](const PeopleIt& lhs, const PeopleIt& rhs) {
      return lhs->name < rhs->name;
    });
    const string* most_popular_name = &((*first)->name);
    int count = 1;
    for (auto i = first; i != last; ) {
      auto same_name_end = find_if_not(i, last, [i](const PeopleIt& it) {
        return it->name == (*i)->name;
      });
      auto cur_name_count = std::distance(i, same_name_end);
      if (cur_name_count > count) {
        count = cur_name_count;
        most_popular_name = &((*i)->name);
      }
      i = same_name_end;
    }
    return *most_popular_name;
  }
public:
  DemographyStats(const vector<Person>& data) {
    // LOG_DURATION("Init DemographyStats in");
    // fill people iterators
    people.reserve(data.size());
    for (auto it = data.begin(); it != data.end(); ++it) {
      people.push_back(it);
    }

    // partition males
    auto first_female_it = partition(begin(people), end(people), [](const PeopleIt& p) {
      return p->is_male;
    });

    male_popular_name = FindMostPopularName(begin(people), first_female_it);
    female_popular_name = FindMostPopularName(first_female_it, end(people));

    // wealth
    sorted_by_wealth = people;
    sort(sorted_by_wealth.begin(), sorted_by_wealth.end(), [](const PeopleIt& lhs, const PeopleIt& rhs) {
      return lhs->income > rhs->income;
    });
  }

  int GetTotalIncomeOf(int count) const {
    auto head = Head(sorted_by_wealth, count);
    return accumulate(
      head.begin(), head.end(), 0, [](int cur, const PeopleIt& p) {
        return cur + p->income;
      }
    );
  }

  const optional<string>& GetPopularNameOf(char gender) const {
    if (gender == 'M') {
      return male_popular_name;
    }
    return female_popular_name;
  }
};

int main() {
  // ostringstream out;
  // stringstream ss = GenPopulation();

  const vector<Person>& people = []{
    // LOG_DURATION("Fill stats in");
    vector<Person> data(ReadPeople(cin));
    sort(begin(data), end(data), [](const Person& lhs, const Person& rhs) {
      return lhs.age < rhs.age;
    });
    return data;
  }();

  const DemographyStats stats(people);

  {
    // LOG_DURATION("Execute demography stats in");
    for (string command; cin >> command; ) {
      if (command == "AGE") {
        int adult_age;
        cin >> adult_age;

        auto adult_begin = lower_bound(
          begin(people), end(people), adult_age, [](const Person& lhs, int age) {
            return lhs.age < age;
          }
        );

        cout << "There are " << std::distance(adult_begin, end(people))
             << " adult people for maturity age " << adult_age << '\n';
      } else if (command == "WEALTHY") {
        int count;
        cin >> count;

        int total_income = stats.GetTotalIncomeOf(count);

        cout << "Top-" << count << " people have total income " << total_income << '\n';
      } else if (command == "POPULAR_NAME") {
        char gender;
        cin >> gender;

        const optional<string>& most_popular_name = stats.GetPopularNameOf(gender);

        if (most_popular_name) {
          cout << "Most popular name among people of gender " << gender << " is "
               << *most_popular_name << '\n';
        } else {
          cout << "No people of gender " << gender << '\n';
        }
      }
    }
  }
}
