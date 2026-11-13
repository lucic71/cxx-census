#include <stdlib.h>

int cleanup(int n) {
  char *a = malloc(n);
  if (!a)
    goto fail;
  if (n > 4)
    goto done;
  a[0] = 1;
done:
  free(a);
  return 0;
fail:
  return -1;
}

int into_block(int n) {
  if (n)
    goto inner;
  {
  inner:
    n++;
  }
  return n;
}

int computed(int n) {
  static void *table[] = {&&a, &&b};
  goto *table[n & 1];
a:
  return 1;
b:
  return 2;
}
