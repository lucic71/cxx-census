int supported(int x) {
  int r = 0;
  switch (x) {
  case 1:
  case 2:
    r = 1;
    break;
  again:
  case 3:
    r = 3;
    break;
  default:
    r = -1;
  }
  return r;
}

int before_case(int x) {
  switch (x) {
    x += 1;
  case 1:
    return 1;
  }
  return 0;
}

void duff(char *to, const char *from, int count) {
  int n = (count + 7) / 8;
  switch (count % 8) {
  case 0:
    do {
      *to++ = *from++;
    case 7:
      *to++ = *from++;
    case 6:
      *to++ = *from++;
    } while (--n > 0);
  }
}

int no_block(int x) {
  switch (x)
  case 1:
    return 1;
  return 0;
}
