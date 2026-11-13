#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void raw(void) {
  struct termios t;
  tcgetattr(0, &t);
  cfmakeraw(&t);
  tcsetattr(0, TCSANOW, &t);
}

int plain(void) { return isatty(1) + puts("x"); }
