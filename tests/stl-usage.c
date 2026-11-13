#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pair {
  int a, b;
};

int use(void) {
  struct Pair arr[2];
  arr->a = 1;
  (arr + 1)->b = 2;
  char *s = malloc(8);
  strcpy(s, "x");
  printf("%s %d\n", s, arr->a + arr[1].b);
  free(s);
  return EXIT_SUCCESS;
}
