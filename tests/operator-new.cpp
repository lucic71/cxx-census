#include <cstddef>
#include <new>

struct Pooled {
  static void *operator new(std::size_t n);
  static void operator delete(void *p);
  static void *operator new[](std::size_t n);
  static void operator delete[](void *p);
  int X;
};

void *operator new(std::size_t n, int tag);

int use() {
  int buf[4];
  int *p = new (buf) int(3);
  int *q = new int(4);
  int r = *p + *q;
  delete q;
  return r;
}
