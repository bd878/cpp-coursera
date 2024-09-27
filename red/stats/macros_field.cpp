#include <iostream>

using namespace std;

struct User {
  string name, surname, id;
};

int main() {
  User player{"Ivan", "Danilov", "1"};

#define GLUE_HELPER(obj, field) ##field
#define SHOW_FIELD(obj, field) GLUE_HELPER(obj, field)

  SHOW_FIELD(player, "name");

  return 0;
}