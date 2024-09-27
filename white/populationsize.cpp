#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Person {
  string name;
  string surname;
  int age;
};

void printPopulationSize(const vector<Person> &population) {
  cout << "Moscow population is " << population.size() << " people" << endl;
}

vector<Person> getPopulation() {
  return {{"Ivan", "Uskov", 25}, {"Yuri", "Pugin", 16}, {"Vladimir", "Chiriac", 22}};
}

int main() {
  auto start = steady_clock::now();
  vector<Person> population = getPopulation();
  auto finish = steady_clock::now();
  cout << "getPopulation: " << duration_cast<milliseconds>(finish - start).count() << "ms" << endl;

  start = steady_clock::now();
  printPopulationSize(population);
  finish = steady_clock::now();
  cout << "printPopulationSize: " << duration_cast<milliseconds>(finish - start).count() << "ms" << endl;

  return 0;
}