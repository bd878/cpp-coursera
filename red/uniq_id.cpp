#include <string>
#include <vector>
using namespace std;

#define GLUE(x, y) x##y
#define GLUE_HELPER(x, y) GLUE(x, y)
#define UNIQ_ID GLUE_HELPER(var, __LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}