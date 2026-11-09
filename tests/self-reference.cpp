struct Node {
  Node *Next;
  Node(Node *N) : Next(N) {}
};

struct Owner {
  Node Head;
  Owner() : Head(reinterpret_cast<Node *>(this)) {}
};

struct Selfish {
  Selfish *This = this;
  int A = 1;
  int B = A + 1;
  int C;
  int D;
  int E;
  Selfish(int a, int b) : C(A), D(compute()), E(b) {}
  int compute() const { return 3; }
};

struct Plain {
  int X;
  Plain() : X(1) {}
};

Node Global(&Global);

void locals() {
  Node Self(&Self);
  Node Other(nullptr);
  Node Chain(&Other);
  static Node Stat(&Stat);
  int Y = 1;
  int &R = R;
  (void)Y;
}
