#include <utility>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

void PrintStats(vector<Person> persons) {
  static vector<pair<string, bool (*)(const Person&)>> filters {
    {"Median age = ", [](const Person& p) { return true; }},
    {"Median age for females = ", [](const Person& p) { return p.gender == Gender::FEMALE; }},
    {"Median age for males = ", [](const Person& p) { return p.gender == Gender::MALE; }},
    {"Median age for employed females = ", [](const Person& p) { return p.gender == Gender::FEMALE && p.is_employed; }},
    {"Median age for unemployed females = ", [](const Person& p) { return p.gender == Gender::FEMALE && !p.is_employed; }},
    {"Median age for employed males = ", [](const Person& p) { return p.gender == Gender::MALE && p.is_employed; }},
    {"Median age for unemployed males = ", [](const Person& p) { return p.gender == Gender::MALE && !p.is_employed; }}
  };

  for (const auto &[title, condition] : filters) {
    auto boundary = partition(begin(persons), end(persons), condition);
    cout << title << (ComputeMedianAge(begin(persons), boundary));
    cout << endl;
  }
}
