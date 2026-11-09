struct Flags {
  unsigned A : 1;
  unsigned B : 3;
  int Plain;
  bool C : 1;
};

template <int N> struct Packed {
  unsigned V : N;
};
Packed<5> P;
