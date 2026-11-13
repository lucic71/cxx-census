#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

void raw() {
  struct termios t;
  tcgetattr(0, &t);
  cfmakeraw(&t);
  tcsetattr(0, TCSANOW, &t);
}

int plain() {
  struct winsize w;
  ioctl(1, TIOCGWINSZ, &w);
  return isatty(1) + puts("x");
}
