#include <forward_list>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

template <typename Type, typename Hasher>
class HashSet {
public:
  using BucketList = forward_list<Type>;

public:
  explicit HashSet(
    size_t num_buckets,
    const Hasher& hasher = {}
  ) : buckets(num_buckets), hash_function(hasher) {};

  void Add(const Type& value) {
    RehashIfNeeded(value);
    if (!Has(value)) {
      buckets[hash_function(value)].push_front(value);
    }
  }

  bool Has(const Type& value) const {
    size_t bucket_id = hash_function(value);
    if (bucket_id >= buckets.size()) {
      return false;
    }

    const BucketList& bucket_list = GetBucket(value);
    auto it = find(bucket_list.begin(), bucket_list.end(), value);

    return it != bucket_list.end();
  }

  void Erase(const Type& value) {
    if (Has(value)) {
      BucketList& bucket_list = buckets[hash_function(value)];
      bucket_list.remove(value);
    }
  }

  const BucketList& GetBucket(const Type& value) const {
    return buckets.at(hash_function(value));
  }
private:
  void RehashIfNeeded(const Type& value) {
    size_t bucket_id = hash_function(value);
    if (bucket_id >= buckets.size()) {
      buckets.resize(bucket_id + 1);
    }
  }
private:
  Hasher hash_function;
  vector<BucketList> buckets;
};
