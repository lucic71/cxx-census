struct regs {
  volatile unsigned int status;
  unsigned int plain;
};

int poll(struct regs *r, volatile int *flag) {
  r->status = 1;
  r->plain = 2;
  (*flag)++;
  return r->status + r->plain + *flag;
}
