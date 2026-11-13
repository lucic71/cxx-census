int add(int a, int b) {
  int r;
  __asm__("addl %2, %0" : "=r"(r) : "0"(a), "r"(b));
  return r;
}

int plain(int a) { return a + 1; }
