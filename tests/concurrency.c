#include <pthread.h>
#include <stdatomic.h>

static void *run(void *arg) { return arg; }

_Atomic int counter;
_Thread_local int local;

int use(void) {
  pthread_t t;
  pthread_create(&t, 0, run, 0);
  pthread_join(t, 0);
  __atomic_fetch_add(&local, 1, __ATOMIC_SEQ_CST);
  return atomic_load(&counter);
}
