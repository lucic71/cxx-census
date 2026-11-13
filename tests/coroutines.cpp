#include <coroutine>

struct Task {
  struct promise_type {
    Task get_return_object() { return {}; }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    std::suspend_always yield_value(int) { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
};

Task gen() {
  co_yield 1;
  co_await std::suspend_always{};
  co_return;
}

int plain() { return 1; }
