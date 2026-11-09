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
  return d ? 1 : 0;
}
