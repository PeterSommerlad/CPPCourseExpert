#ifndef THREADSAFEQUEUE_H_
#define THREADSAFEQUEUE_H_

#include <condition_variable>
#include <mutex>
#include <optional>
#include<chrono>
namespace TSQ {
template<typename T, typename MUTEX = std::mutex>
struct ThreadsafeExchange {
  void push(T const &t) {
    std::unique_lock lk { mx };
    notFull.wait(lk, [this]() {
      return not q.has_value();
    });
    q.emplace(t);
    notEmpty.notify_one();
  }
  bool try_push(T const &t) {
    std::scoped_lock const lk { mx };
    if (not q.has_value()){
      q.emplace(t);
      notEmpty.notify_one();
      return true;
    }
    return false;
  }
  template <typename Rep, typename Period>
  bool try_push_for(T const &t, std::chrono::duration<Rep,Period> dur) {
    std::unique_lock lk { mx };
    if (notFull.wait_for(lk, dur, [this]() {
      return not q.has_value();
    })) {
      q.emplace(t);
      notEmpty.notify_one();
      return true;
    } else {
      return false;
    }
  }
  // always blocks for lazyness
  T pop() {
    std::unique_lock lk { mx };
    notEmpty.wait(lk, [this] {
      return q.has_value();
    });
    T t = q.value();
    q.reset();
    notFull.notify_one();
    return t;
  }
  // don't call when holding a lock!
  bool empty() const {
    std::scoped_lock const lk { mx };
    return not q.has_value();
  }
  // cannot be noexcept, because (un-)locking might fail
  void swap(ThreadsafeExchange &other) {
    if (this == &other) {
      return;
    }
    std::scoped_lock const both { mx, other.mx };
    // no need to swap cv or mx
    std::swap(q, other.q);
    if (q.has_value()) {
      notEmpty.notify_one();
    } else {
      notFull.notify_one();
    }
    if (other.q.has_value()) {
      other.notEmpty.notify_one();
    } else {
      other.notFull.notify_one();
    }

  }
  friend void swap(ThreadsafeExchange &left, ThreadsafeExchange &other) {
    left.swap(other);
  }
private:
  mutable MUTEX mx { };
  std::condition_variable notEmpty { };
  std::condition_variable notFull { };
  std::optional<T> q { };
};
}

#endif /* THREADSAFEQUEUE_H_ */
