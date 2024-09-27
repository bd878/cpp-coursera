#include <iomanip>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class ReadingManager {
private:
  static const int PAGES = 1000;
  static const int USERS = 100'000;
public:
  using UserId = int;
  using Page = int;

  ReadingManager()
    : users_pages(USERS + 1, 0),
      users_count(PAGES + 1, 0) {}

  void Read(UserId user_id, Page page_count) {
    if (users_pages[user_id] != 0) {
      DecreaseUsersCount(users_pages[user_id]);
    }
    IncreaseUsersCount(page_count);
    users_pages[user_id] = page_count;
  }

  double Cheer(UserId user_id) const {
    if (users_pages[user_id] == 0) {
      return 0;
    }

    int user_count = users_count.back();
    if (user_count == 1) {
      return 1;
    }

    int less_user_count = users_count.at(users_pages.at(user_id) - 1);
    if (less_user_count == 0) {
      return 0;
    }

    // По умолчанию деление целочисленное, поэтому
    // нужно привести числитель к типу double.
    // Простой способ сделать это — умножить его на 1.0.
    return (less_user_count * 1.0) / (user_count - 1);
  }

private:
  vector<int> users_pages;
  vector<int> users_count;

  void IncreaseUsersCount(Page from) {
    for (int i = from; i < users_count.size(); ++i) {
      ++users_count[i];
    }
  }

  void DecreaseUsersCount(Page from) {
    for (int i = from; i < users_count.size(); ++i) {
      --users_count[i];
    }
  }
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

//   istringstream iss(R"(
// 12
// CHEER 5
// READ 1 10
// CHEER 1
// READ 2 5
// READ 3 7
// CHEER 2
// CHEER 3
// READ 3 10
// CHEER 3
// READ 3 11
// CHEER 3
// CHEER 1
//   )");

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}