#include <dlfcn.h>

typedef int (*Fn)(int);

int load(const char *path) {
  void *h = dlopen(path, RTLD_NOW);
  if (!h) {
    const char *e = dlerror();
    (void)e;
    return 0;
  }
  Fn f = reinterpret_cast<Fn>(dlsym(h, "compute"));
  int r = f ? f(1) : 0;
  dlclose(h);
  return r;
}

int plain(int x) { return x + 1; }
