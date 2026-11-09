struct OnlyNonConst {
  OnlyNonConst() = default;
  OnlyNonConst(OnlyNonConst &);
};

struct Both {
  Both(Both &);
  Both(const Both &);
};

struct Deleted {
  Deleted(Deleted &) = delete;
};

struct Normal {
  Normal(const Normal &);
};

struct Holder {
  OnlyNonConst Member;
};

template <class T> struct Wrap {
  Wrap(Wrap &);
};
Wrap<int> W(*(Wrap<int> *)nullptr);

void copies(OnlyNonConst &o, Holder &h) {
  OnlyNonConst c(o);
  Holder hc(h);
  (void)c;
  (void)hc;
}
