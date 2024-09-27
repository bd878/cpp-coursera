#include <deque>
#include <future>
#include <unordered_map>
#include <algorithm>

#include "cache_common.h"

using namespace std;

class LruCache : public ICache {
private:
  const Settings& settings;
  shared_ptr<IBooksUnpacker> unpacker;
  size_t bytes_left;
  unordered_map<string, BookPtr> content;
  deque<string> priorities;
  mutex m;
public:
  LruCache(
      shared_ptr<IBooksUnpacker> u,
      const Settings& s
  ) : unpacker(u), settings(s), bytes_left(s.max_memory) {}

  BookPtr GetBook(const string& book_name) override {
    lock_guard<mutex> g(m);

    if (content.count(book_name)) {
      auto it = find(priorities.begin(), priorities.end(), book_name);
      priorities.erase(it);
      priorities.push_front(book_name);
      return content.at(book_name);
    }

    BookPtr book = unpacker->UnpackBook(book_name);
    if (book->GetContent().size() > settings.max_memory) {
      return book;
    }

    while (book->GetContent().size() > bytes_left) {
      const string& name = priorities.back();
      bytes_left += content[name]->GetContent().size();
      content.erase(name);
      priorities.pop_back();
    }

    content[book_name] = book;
    priorities.push_front(book_name);
    bytes_left -= book->GetContent().size();

    return book;
  }
};


unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings
) {
  return make_unique<LruCache>(
    books_unpacker,
    settings
  );
}
