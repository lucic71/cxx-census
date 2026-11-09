unsigned long rdtsc() {
  unsigned lo, hi;
  __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
  return ((unsigned long)hi << 32) | lo;
}

void pause() { asm volatile("pause"); }

int plain(int x) { return x * 2; }
