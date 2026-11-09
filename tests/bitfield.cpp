#include <cstddef>
#include <cstdio>
#include <cstring>

struct Flags {
  unsigned A : 1;
  unsigned B : 3;
  int Plain;
};

struct Wire {
  unsigned Version : 4;
  unsigned Type : 4;
  unsigned Length;
};

struct Saved {
  unsigned Dirty : 1;
};

struct Punned {
  bool Set : 1;
};

struct Laid {
  unsigned X : 2;
  int Y;
};

struct __attribute__((packed)) Packed {
  char C;
  int I;
};

struct Virt {
  virtual void f();
  int I;
};

union Pun {
  float F;
  unsigned U;
};

struct Base {
  int B;
};
struct Derived : Base {
  int D;
};

#pragma pack(push, 1)
struct PragmaPacked {
  char C;
  int I;
};
#pragma pack(pop)

struct __attribute__((packed)) UnobservedPacked {
  char C;
  short S;
};

struct UnobservedVirt {
  virtual void g();
};

void use(Flags &f, Wire &w, Saved &s, Punned &p, FILE *out) {
  f.A = 1;
  char buf[sizeof(Wire)];
  std::memcpy(buf, &w, sizeof(w));
  fwrite(&s, sizeof s, 1, out);
  const unsigned char *bytes = reinterpret_cast<const unsigned char *>(&p);
  (void)bytes;
  (void)offsetof(Laid, Y);
  (void)sizeof(Packed);
  Virt v;
  std::memset(&v, 0, sizeof v);
  Pun u;
  u.F = 1.0f;
  (void)u.U;
  (void)sizeof(Pun);
  Derived d;
  fwrite(&d, sizeof d, 1, out);
  UnobservedVirt uv;
  (void)uv;
}
