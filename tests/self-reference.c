struct List {
  struct List *next;
};

struct List head = {&head};

int use(void) {
  struct List local = {&local};
  int plain = 1;
  return local.next == &local ? plain : 0;
}
