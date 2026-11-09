#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <functional>
#include <string_view>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <limits>
#include <map>
#include <string>
#include <vector>

struct Own {
  int X;
  int get() const { return X; }
};

uint8_t clamp(float v) {
  return (uint8_t)std::max(0.0f, std::min(255.0f, v));
}

int use() {
  std::array<int, 2> arr = {1, 2};
  std::vector<bool> bits(4);
  std::atomic<int> counter{0};
  counter.fetch_add(1);
  std::bitset<4> flags;
  flags.set(1);
  std::vector<int> init = {1, 2, 3};
  std::function<int(int)> fn = [](int x) { return x; };
  fn(1);
  std::string_view sv = "x";
  (void)sv.begin();
  (void)flags.size();
  (void)flags[1];
  (void)(flags == flags);
  (void)bits[0];
  bits.push_back(true);
  std::vector<uint8_t> buf(16);
  buf.resize(32);
  std::string s = "hello";
  std::map<int, float> m;
  m[1] = 2.0f;
  float f = m.at(1);
  Own o{1};
  std::memcpy(buf.data(), s.c_str(), s.size());
  printf("%zu %d\n", buf.size(), o.get());
  return std::numeric_limits<int16_t>::max() + (int)f + clamp(3.0f);
}
