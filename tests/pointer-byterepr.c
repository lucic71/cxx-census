#include <stdlib.h>
#include <string.h>

struct Node {
  struct Node *next;
  int value;
};

struct Plain {
  int a, b;
};

union Pun {
  int *p;
  long l;
};

union Bytes {
  int i;
  char c[4];
};

int use(void) {
  struct Node *n = malloc(sizeof(struct Node));
  struct Plain *p = malloc(sizeof(struct Plain));
  char *raw = (char *)n;
  struct Node *back = (struct Node *)raw;
  long addr = (long)n;
  int *fake = (int *)8;
  char *praw = (char *)p;
  free(n);
  free(p);
  return (int)addr + (back != 0) + (fake != 0) + praw[0];
}

struct list_head {
  struct list_head *next, *prev;
};

struct item {
  int val;
  struct list_head node;
};

struct item *kernel_container_of(struct list_head *p) {
  return (struct item *)((void *)p - __builtin_offsetof(struct item, node));
}
