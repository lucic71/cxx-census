int supported(int x) {
  switch (x) {
  case 1:
  case 2:
    return 1;
  default:
    return 0;
  }
}

int before_case(int x) {
  switch (x) {
    x++;
  case 1:
    return x;
  }
  return 0;
}

void duff(char *to, const char *from, int count) {
  int n = (count + 3) / 4;
  switch (count % 4) {
  case 0:
    do {
      *to++ = *from++;
    case 3:
      *to++ = *from++;
    } while (--n > 0);
  }
}
