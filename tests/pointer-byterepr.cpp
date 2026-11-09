#include <cstdint>
#include <cstdlib>
#include <cstring>

struct Node {
  int Value;
  Node *Next;
};

struct Wrapper {
  Node Inner[2];
};

struct Derived : Wrapper {
  int X;
};

struct Plain {
  int A;
  double B;
};

void allocs() {
  Node *n = (Node *)malloc(sizeof(Node));
  Wrapper *w = static_cast<Wrapper *>(calloc(1, sizeof(Wrapper)));
  Derived *d = reinterpret_cast<Derived *>(realloc(nullptr, sizeof(Derived)));
  Plain *p = (Plain *)malloc(sizeof(Plain));
  int *i = (int *)malloc(sizeof(int));
  void *v = malloc(4);
  free(n); free(w); free(d); free(p); free(i); free(v);
}

uintptr_t casts(int *p) {
  uintptr_t addr = (uintptr_t)p;
  intptr_t s = reinterpret_cast<intptr_t>(p);
  int *back = (int *)addr;
  int *fromLiteral = reinterpret_cast<int *>(0x1000);
  int *null = 0;
  bool b = p;
  (void)back; (void)fromLiteral; (void)null; (void)b;
  return addr + s;
}

void callback(void *);

void bytes(Node &node, Plain &plain, char *buffer) {
  Node other;
  std::memcpy(&node, &other, sizeof(Node));
  char *raw = reinterpret_cast<char *>(&node);
  Node *parsed = (Node *)buffer;
  char *plainRaw = reinterpret_cast<char *>(&plain);
  Plain *plainParsed = (Plain *)buffer;
  callback((void *)&node);
  (void)raw; (void)parsed; (void)plainRaw; (void)plainParsed;
}
