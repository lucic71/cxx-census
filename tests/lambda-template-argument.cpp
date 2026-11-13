#include <cstdio>
#include <memory>
#include <queue>
#include <set>
#include <vector>

auto cmp = [](int a, int b) { return a > b; };

struct Holder {
  std::set<int, decltype(cmp)> S;
};

void uses() {
  std::set<int, decltype(cmp)> a;
  std::set<int, decltype(cmp)> b(cmp);
  std::priority_queue<int, std::vector<int>, decltype(cmp)> q;
  auto closer = [](FILE *f) { fclose(f); };
  std::unique_ptr<FILE, decltype(closer)> f(fopen("x", "r"), closer);
  std::set<int> plain;
  auto l = [] { return 1; };
  (void)l;
}
