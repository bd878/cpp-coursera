#include <vector>
#include <iostream>
#include <utility>

using namespace std;

struct Node {
  int as_int;
  vector<Node> as_array;
  Node(int i) : as_int(i), as_array({}) {};
  explicit Node(vector<Node> array) : as_array(move(as_array)) {};
};

int main() {
  vector<Node> heavy_nodes = {1, 2, 3, 4, 5};
  cout << heavy_nodes.size() << '\n';
  Node array_node(move(heavy_nodes));
  cout << heavy_nodes.size() << '\n';
  return 0;
}
