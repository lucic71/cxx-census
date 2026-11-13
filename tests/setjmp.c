#include <setjmp.h>
#include <ucontext.h>

static jmp_buf env;

static void fail(void) { longjmp(env, 1); }

int run(void) {
  if (setjmp(env))
    return -1;
  fail();
  return 0;
}

int ctx(void) {
  ucontext_t a, b;
  getcontext(&a);
  return swapcontext(&a, &b);
}

int builtin(void) {
  void *buf[5];
  if (__builtin_setjmp(buf))
    return 1;
  __builtin_longjmp(buf, 1);
}
