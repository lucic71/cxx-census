struct Error {};

void thrower(int x) {
  if (x)
    throw Error{};
  throw 42;
}

int catcher() {
  try {
    thrower(1);
  } catch (const Error &) {
    return 1;
  } catch (int) {
    return 2;
  } catch (...) {
    throw;
  }
  return 0;
}

struct FunctionTry {
  FunctionTry() try : X(0) {
  } catch (...) {
  }
  int X;
};

template <class T> void templated(T t) { throw t; }
void instantiate() { templated(1.0); }
