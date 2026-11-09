#include <new>

struct Widget {
  int X;
};

void placement(void *buf) {
  Widget *w = new (buf) Widget;
  Widget *arr = new (buf) Widget[3];
  Widget *nt = new (std::nothrow) Widget;
  Widget *plain = new Widget;
  Widget *plainArr = new Widget[2];
  w->~Widget();
  delete nt;
  delete plain;
  delete[] plainArr;
  (void)arr;
}
