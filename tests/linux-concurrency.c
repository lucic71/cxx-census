typedef struct {
  int counter;
} atomic_t;

typedef struct spinlock {
  int raw;
} spinlock_t;

struct mutex {
  atomic_t owner;
};

void spin_lock(spinlock_t *l);
void mutex_lock(struct mutex *m);
int atomic_inc_return(atomic_t *v);

struct dev {
  spinlock_t lock;
  struct mutex m;
  atomic_t refs;
  int plain;
};

int use(struct dev *d) {
  int *p = &d->plain;
  spin_lock(&d->lock);
  mutex_lock(&d->m);
  return atomic_inc_return(&d->refs) + *p;
}
