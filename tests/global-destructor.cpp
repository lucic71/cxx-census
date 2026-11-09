#include <string>
#include <vector>

struct Trivial {
  int X;
};

struct WithDtor {
  ~WithDtor();
};

Trivial T;
WithDtor W;
std::string S = "x";
std::vector<int> V;
static WithDtor Arr[2];
extern WithDtor Declared;
int I = 0;

struct Holder {
  static WithDtor Member;
};
WithDtor Holder::Member;

void f() {
  static WithDtor Local;
  WithDtor Automatic;
  (void)Automatic;
}
