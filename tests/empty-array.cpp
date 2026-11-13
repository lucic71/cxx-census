#include <array>

struct Holder {
  std::array<int, 0> Empty;
  std::array<int, 3> Full;
};

template <int N> int size() {
  std::array<int, N> a{};
  return (int)a.size();
}

int use() {
  std::array<double, 0> b{};
  return size<0>() + size<2>() + (int)b.size();
}
