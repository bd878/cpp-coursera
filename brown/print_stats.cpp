#include <algorithm>
#include <iostream>

using namespace std;

/*
Median age = 40
Median age for females = 40
Median age for males = 55
Median age for employed females = 40
Median age for unemployed females = 80
Median age for employed males = 55
Median age for unemployed males = 78
 */

void PrintStats(vector<Person> persons) {
  auto male_it = partition(persons.begin(), persons.end(), [](const Person& p){ return p.gender == Gender::FEMALE; });
  auto unemployed_female_it = partition(persons.begin(), male_it, [](const Person& p){ return p.is_employed; });
  auto unemployed_male_it = partition(male_it, persons.end(), [](const Person& p){ return p.is_employed; });

  cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << '\n'
    << "Median age for females = " << ComputeMedianAge(persons.begin(), male_it) << '\n'
    << "Median age for males = " << ComputeMedianAge(male_it, persons.end()) << '\n'
    << "Median age for employed females = " << ComputeMedianAge(persons.begin(), unemployed_female_it) << '\n'
    << "Median age for unemployed females = " << ComputeMedianAge(unemployed_female_it, male_it) << '\n'
    << "Median age for employed males = " << ComputeMedianAge(male_it, unemployed_male_it) << '\n'
    << "Median age for unemployed males = " << ComputeMedianAge(unemployed_male_it, persons.end()) << endl;
}
