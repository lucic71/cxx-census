#include <algorithm>
#include <iterator>
#include <optional>
#include <ranges>
#include <tuple>
#include <utility>
#include <vector>

int uses(std::vector<int> &v, std::vector<std::vector<int>> &vv) {
  std::ranges::sort(v);
  auto it = std::ranges::begin(v);
  it = std::ranges::next(it);
  auto evens = v | std::views::filter([](int x) { return x % 2 == 0; });
  auto flat = vv | std::views::join;
  for (auto [i, x] : std::views::enumerate(v))
    (void)i, (void)x;
  decltype(std::views::split) *p = nullptr;
  (void)p;
  int n = 0;
  for (int x : evens)
    n += x;
  for (int x : flat)
    n += x;
  return n + *it;
}

int plain(std::vector<int> &v) {
  std::sort(v.begin(), v.end());
  std::optional<int> o = std::nullopt;
  std::pair<int, int> p(std::piecewise_construct, std::tuple<int>(1),
                        std::tuple<int>(2));
  int a;
  std::tie(a, std::ignore) = p;
  return a + o.value_or(0) + *std::begin(v);
}
