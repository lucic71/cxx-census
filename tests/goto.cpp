int supported(int n) {
  int i = 0;
again:
  if (i < n) {
    ++i;
    goto again;
  }
  for (int j = 0; j < n; ++j) {
    if (j == 3)
      goto done;
  }
done:
  return i;
}

int nested_label(int n) {
  while (n > 0) {
    --n;
    if (n == 5)
      goto skip;
    n -= 1;
  skip:
  first:
    continue;
  }
  return n;
}

int label_in_if(int n) {
  if (n > 0)
  inside:
    --n;
  if (n > 0)
    goto inside;
  return n;
}

int into_loop(int n) {
  goto body;
  while (n > 0) {
  body:
    --n;
  }
  return n;
}

int computed(int n) {
  void *t[] = {&&a, &&b};
  goto *t[n & 1];
a:
  return 1;
b:
  return 2;
}
