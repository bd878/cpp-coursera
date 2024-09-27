#pragma once

#include <optional>
#include <utility>
#include <functional>

template <typename T>
class LazyValue {
public:
  explicit LazyValue(std::function<T()>);

  bool HasValue() const;
  const T& Get() const;

private:
  mutable std::optional<T> value;
  std::function<T()> init;
};

template <typename T>
LazyValue<T>::LazyValue(std::function<T()> initializer)
  : init(move(initializer)) {}

template <typename T>
bool LazyValue<T>::HasValue() const {
  return static_cast<bool>(value);
}

template <typename T>
const T& LazyValue<T>::Get() const {
  if (!HasValue()) {
    value = init();
  }

  return *value;
}
