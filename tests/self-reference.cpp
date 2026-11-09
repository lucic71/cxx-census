struct Node {
  Node *Next;
  Node(Node *N) : Next(N) {}
};

struct Owner {
  Node Head;
  Owner() : Head(reinterpret_cast<Node *>(this)) {}
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
