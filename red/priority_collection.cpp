#include "test_runner.h"
#include <list>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename It>
struct PriorityItem {
  It value;
  int order = 0;
  int priority = 0;

  friend bool operator==(const PriorityItem& lhs, const PriorityItem& rhs) {
    return *(lhs.value) == *(rhs.value);
  }
  friend bool operator<(const PriorityItem& lhs, const PriorityItem& rhs) {
    return *(lhs.value) < *(rhs.value);
  }
};

template <typename T>
class PriorityCollection {
public:
  using Id = typename list<T>::iterator;
  using MetaIt = typename set<PriorityItem<Id>>::const_iterator;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
    auto object_it = items.insert(items.end(), move(object));
    items_meta.insert({object_it, GetOrder()});
    return object_it;
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
    return static_cast<bool>(items_meta.count({id}));
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
    return *id;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
    auto meta_it = items_meta.find({id});
    auto hint = next(meta_it);

    PriorityItem<Id> meta(move(*meta_it));
    meta.priority += 1;

    items_meta.erase(meta_it);
    items_meta.insert(hint, meta);
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const {
    MetaIt max_item_meta = GetMaxPriorityItem();
    return {*(max_item_meta->value), max_item_meta.priority};
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax() {
    auto meta_it = GetMaxPriorityItem();

    int priority = meta_it->priority;
    T value = move(*(meta_it->value));

    items.erase(meta_it->value);
    items_meta.erase(meta_it);

    return {move(value), priority};
  }
private:
  int order = 0;
  list<T> items;
  set<PriorityItem<Id>> items_meta;

  int GetOrder() {
    return order++;
  }

  MetaIt GetMaxPriorityItem() {
    return max_element(items_meta.begin(), items_meta.end(), [&](const PriorityItem<Id>& lhs, const PriorityItem<Id>& rhs){
      return lhs.priority < rhs.priority && lhs.order < rhs.order;
    });
  }
};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
