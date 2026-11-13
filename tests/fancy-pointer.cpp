#include <cstddef>
#include <cstdio>
#include <memory>
#include <vector>

template <class T> struct Offset {
  std::ptrdiff_t Off;
  T &operator*() const;
};

template <class T> struct FancyAlloc {
  using value_type = T;
  using pointer = Offset<T>;
  pointer allocate(std::size_t);
  void deallocate(pointer, std::size_t);
};

template <class T> struct PlainAlloc {
  using value_type = T;
  T *allocate(std::size_t n) { return std::allocator<T>{}.allocate(n); }
  void deallocate(T *p, std::size_t n) { std::allocator<T>{}.deallocate(p, n); }
};

struct Handle {
  int Fd = -1;
  Handle() = default;
  Handle(std::nullptr_t) {}
  Handle(int f) : Fd(f) {}
  explicit operator bool() const { return Fd >= 0; }
  bool operator==(const Handle &) const = default;
};

struct HandleDeleter {
  using pointer = Handle;
  void operator()(Handle) const {}
};

struct FileCloser {
  void operator()(FILE *f) const { fclose(f); }
};

void use() {
  std::unique_ptr<int, HandleDeleter> h(Handle(3));
  std::unique_ptr<FILE, FileCloser> f(fopen("x", "r"));
  std::vector<int, PlainAlloc<int>> v;
  std::vector<int> w;
}
