#include <vector>
#include <exception>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <set>
#include <utility>

using namespace std;

class ReadingManager {
private:
  static const int MAX_PAGES = 1000;
  static const int MAX_USERS = 100'000;
  vector<int> users_on_pages;
  vector<int> users_pages;
  set<int> users;
public:
  ReadingManager(): users_on_pages(MAX_PAGES, 0), users_pages(MAX_USERS, 0) {}

  void Read(int user_id, int page_count) {
    if (users.count(user_id) > 0) {
      int current_page_count = users_pages[user_id];
      users_on_pages[current_page_count]--;
    }

    users_on_pages[page_count]++;
    users_pages[user_id] = page_count;
    users.insert(user_id);
  }

  double Cheer(int user_id) const {
    int users_count = users.size();
    if (users_count == 1) {
      return 1;
    }

    int pages_count = users_pages[user_id];
    if (pages_count == 0) {
      return 0;
    }

    int position = accumulate(
      users_on_pages.begin(), users_on_pages.begin() + pages_count, 0,
      [](int sum, int page_count_users){
        return sum + page_count_users;
      }
    );

    return (users_count - position) * 1.0 / (users_count - 1);
  }
};

