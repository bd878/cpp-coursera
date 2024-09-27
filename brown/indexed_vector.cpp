#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

struct Sockaddr {
  int addr;
};

bool operator==(const Sockaddr& lhs, const Sockaddr& rhs) {
  return lhs.addr == rhs.addr;
}

int main() {
  vector<Sockaddr> addrs{{6}, {3}, {7}, {2}, {5}};

  using SockaddrIt = typename vector<Sockaddr>::const_iterator;
  vector<SockaddrIt> s_addrs;
  s_addrs.reserve(addrs.size());
  for (auto it = addrs.begin(); it != addrs.end(); ++it) {
    s_addrs.push_back(it);
  }

  sort(s_addrs.begin(), s_addrs.end(), [](const SockaddrIt& lhs, const SockaddrIt& rhs) {
    return (*lhs).addr < (*rhs).addr;
  });

  for (auto it = s_addrs.begin(); it != s_addrs.end(); ++it) {
    cout << (*it)->addr << " ";
  }
  cout << '\n';

  return 0;
}