#include <stddef.h>
#include <string.h>

struct Flags {
  unsigned a : 3;
  unsigned b : 5;
};

struct Hidden {
  unsigned a : 1;
};

struct __attribute__((packed)) Packed {
  char c;
  int i;
};

int use(struct Hidden h) {
  struct Flags f;
  memset(&f, 0, sizeof(struct Flags));
  return f.a + h.a + (int)offsetof(struct Packed, i);
}
