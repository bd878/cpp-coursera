#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

template <typename It>
struct PriorityItem {
  int priority;
  It value;
  friend bool operator==(const PriorityItem& lhs, const PriorityItem& rhs) {
    return lhs.value == rhs.value;
  }
  friend bool operator<(const PriorityItem& lhs, const PriorityItem& rhs) {
    return lhs.priority < rhs.priority;
  }
};

template <typename It, typename PriorityIt>
struct IdItem {
  size_t id;
  It value;
  PriorityIt priority_it;

  friend bool operator==(const IdItem& lhs, const IdItem& rhs) {
    return lhs.value == rhs.value;
  }
  friend bool operator<(const IdItem& lhs, const IdItem& rhs) {
    return lhs.id < rhs.id;
  }
};

template <typename T>
class PriorityCollection {
public:
  using It = typename list<T>::const_iterator;
  using PriorityIt = typename set<PriorityItem<It>>::const_iterator;
  using Id = size_t;
private:
  list<T> items;
  set<PriorityItem<It>> priorities;
  set<IdItem<It>, PriorityIt> ids;

  static const int DEFAULT_PRIORITY = 0;

  size_t id_counter = 0;
  Id GetId() { return ++id_counter; }
public:
  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
    It object_it = items.insert(items.end(), move(object));
    Id id = GetId();
    auto priority_it = priorities.insert({DEFAULT_PRIORITY, object_it});
    ids.insert({id, object_it, priority_it.first});
    return id;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
    for (auto it = range_begin; it != range_end; ++it) {
      size_t gap = distance(range_begin, it);
      *(ids_begin + gap) = Add(*it);
    }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
    return static_cast<bool>(ids.count({id}));
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
    auto item = ids.find({id});
    return *(item.value);
  }
};

int main() {
  PriorityCollection<string> items;
  return 0;
}