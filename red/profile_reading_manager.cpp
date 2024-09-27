#include <fstream>
#include <iomanip>

#include "reading_manager.h"
#include "gen_reading_manager.h"
#include "profile.h"

using namespace std;

int main() {
  genReadAndCheer(100'000, 1'000'000, 1100);

  ifstream fin("readers.txt");
  ofstream fout("readers_stat.txt");

  ReadingManager manager;

  int query_count;
  fin >> query_count;

  {
    LOG_DURATION("ReadingManager");
    for (int query_id = 0; query_id < query_count; ++query_id) { // O(Q)
      string query_type;
      fin >> query_type;
      int user_id;
      fin >> user_id;

      if (query_type == "READ") {
        int page_count;
        fin >> page_count;
        manager.Read(user_id, page_count); // O(N)
      } else if (query_type == "CHEER") {
        fout << setprecision(6) << manager.Cheer(user_id) << "\n"; // O(N)
      }
    }
  }

  return 0;
}
