#include <format>
#include <functional>
#include <string>
#include <vector>

struct Key {
  int A;
};

template <> struct std::hash<Key> {
  std::size_t operator()(const Key &k) const { return k.A; }
};

template <> struct std::formatter<Key> : std::formatter<int> {
  auto format(const Key &k, std::format_context &c) const {
    return std::formatter<int>::format(k.A, c);
  }
};

struct Item {
  int X;
};

template <> constexpr void std::vector<Item>::swap(std::vector<Item> &) noexcept {}

template <class T> struct Mine {};
template <> struct Mine<int> {};

std::size_t use(Key k) { return std::hash<Key>{}(k) + std::hash<int>{}(1); }
