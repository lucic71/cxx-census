#include <dlfcn.h>

typedef int (*Fn)(int);

int load(const char *path) {
  void *h = dlopen(path, RTLD_NOW);
  if (!h)
    return 0;
  Fn f = (Fn)dlsym(h, "compute");
  int r = f ? f(1) : 0;
  dlclose(h);
  return r;
}
