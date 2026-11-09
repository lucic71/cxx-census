#include <atomic>
#include <condition_variable>
#include <coroutine>
#include <future>
#include <mutex>
#include <pthread.h>
#include <shared_mutex>
#include <thread>

thread_local int Counter;
std::atomic<int> Fine;

struct Holder {
  std::mutex M;
  std::atomic<int> A;
  std::condition_variable CV;
  std::shared_mutex *SM;
  std::thread Threads[2];
};

void threads() {
  std::thread T([] {});
  T.join();
  std::jthread J([] {});
  std::lock_guard<std::mutex> G(*(std::mutex *)nullptr);
  auto F = std::async([] { return 1; });
  std::this_thread::yield();
  std::thread([] {}).detach();
  pthread_t P;
  pthread_create(&P, nullptr, [](void *) -> void * { return nullptr; }, nullptr);
  int X = 0;
  __atomic_fetch_add(&X, 1, __ATOMIC_SEQ_CST);
  __sync_fetch_and_add(&X, 1);
}

struct Task {
  struct promise_type {
    Task get_return_object() { return {}; }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
};

Task coro() { co_return; }

void parallel(int *a, int n) {
#pragma omp parallel for
  for (int i = 0; i < n; ++i)
    a[i] = i;
}

struct Plain {
  int X;
  void f() {}
};
