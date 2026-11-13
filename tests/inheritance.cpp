#include <typeinfo>

struct PureBase {
  virtual ~PureBase() = default;
  virtual int f() const = 0;
};
struct Supported : PureBase {
  int f() const override { return 1; }
};

struct DefaultMethodBase {
  virtual ~DefaultMethodBase() = default;
  virtual int f() const = 0;
  virtual int g() const { return 0; }
};
struct DerivedDefault : DefaultMethodBase {
  int f() const override { return 1; }
};

struct DataBase {
  virtual int f() const = 0;
  int X;
};
struct DerivedData : DataBase {
  int f() const override { return X; }
};

struct ConcreteBase {
  int helper() const { return 1; }
  virtual int f() const = 0;
};
struct DerivedConcrete : ConcreteBase {
  int f() const override { return helper(); }
};

struct NonAbstract {
  virtual void f() {}
};
struct DerivedNonAbstract : NonAbstract {};

struct Plain {};
struct DerivedPlain : private Plain {};

#include <type_traits>
struct Tag : std::true_type {};
struct Opaque {};
struct FromOpaque : Opaque {
  int X;
};

struct A {
  virtual void a() = 0;
};
struct B {
  virtual void b() = 0;
};
struct Multi : A, B {
  void a() override {}
  void b() override {}
};

struct VirtBase : virtual PureBase {
  int f() const override { return 2; }
};

struct CtorBase {
  CtorBase(int) {}
  virtual ~CtorBase() {}
  virtual void f() = 0;
};
struct DerivedCtor : CtorBase {
  DerivedCtor() : CtorBase(1) {}
  void f() override {}
};

template <class T> struct TBase {
  virtual T get() = 0;
  T Cached;
};
struct DerivedT : TBase<int> {
  int get() override { return Cached; }
};

int uses(PureBase *p, NonAbstract &r) {
  auto *d = dynamic_cast<Supported *>(p);
  auto &rr = dynamic_cast<DerivedNonAbstract &>(r);
  (void)rr;
  (void)typeid(*p);
  (void)typeid(Supported);
  (void)typeid(p);
  return d ? 1 : 0;
}

int upcasts(DerivedConcrete &dc, DerivedData *dd, Supported *s) {
  ConcreteBase *cb = &dc;
  DataBase &db = *dd;
  PureBase *pb = s;
  int r = dc.helper() + dd->X;
  return cb->f() + db.f() + pb->f() + r;
}

struct PolyRoot {
  virtual ~PolyRoot() {}
};
struct AbstractRoot {
  virtual ~AbstractRoot() = 0;
};

struct Iface {
  virtual ~Iface() {}
  virtual int run() = 0;
};
struct Impl : Iface {
  int run() override { return 1; }
};

struct Template {
  Template() { init(); }
  virtual ~Template() { init(); }
  int describe() { return area() + Template::area(); }
  virtual void init() {}
  virtual int area() { return 0; }
  int X = 0;
  int name() const { return 1; }
  virtual Template *clone() { return this; }
};
struct Square : Template {
  int area() override { return 4; }
  int name() const { return 2; }
  Square *clone() override { return this; }
};

struct Left {
  int L;
  virtual ~Left() {}
};
struct Right {
  int R;
  virtual ~Right() {}
};
struct Both : Left, Right {};

#include <map>
#include <set>

int newuses(Template *t, Template *u, Template *arr, Square &sq, Both &b) {
  Template plain;
  Template copy = sq;
  copy = sq;
  Right *r = &b;
  Square *s = static_cast<Square *>(t);
  std::set<Template *> keys;
  std::map<Template *, int> m;
  void *erased = t;
  int c = (t == u) + (t != nullptr) + (t < u);
  Template *next = arr + 1;
  ++next;
  return c + arr[1].X + r->R + s->X + plain.X + copy.X + (erased != nullptr) +
         (int)keys.size() + (int)m.size() + next->X;
}

struct Writer {
  virtual ~Writer() {}
  virtual int write(int) = 0;
  int flush() { return 0; }
};
struct Mid : Writer {
  int write(int) override { return 1; }
};
struct Leaf : Mid {
  int write(int) override { return 2; }
  int write(double) { return 3; }
  int flush() { return 4; }
};
