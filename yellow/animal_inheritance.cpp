#include <iostream>

using namespace std;

class Animal {
public:
    Animal(const string& name): Name(name) {};

    const string Name;
};


class Dog : public Animal {
public:
    Dog(string name): Animal(name) {};

    void Bark() const {
        cout << Name << " barks: woof!" << endl;
    }
};

int main() {
  const Dog bart("Bart");
  bart.Bark();

  return 0;
}
