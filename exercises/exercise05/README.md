# Exercise 5

In this exercise you will wrap your `BoundedBuffer` in a thread-safe `BoundedQueue`.


## Interface of `BoundedQueue`

Your `BoundedQueue` shall provide the following functionality:

* `push(T)` - Both copy and move / or forwarding. This operation blocks if the `BoundedQueue` is full.
* `T pop()` - Always returns the popped value. This operation blocks if the `BoundedQueue`is empty.
* `bool try_push(T const &)` - Tries to put a `T` into the queue. If the queue is not full and put operation has been successful it returns `true`, otherwise it returns `false`.
* `bool try_pop(T&)` - Tries to pop a `T` from the queue. If the queue is not empty and the pop operation has been suffessful it returns `true` and the popped value is in the out parameter, otherwise it returns `false`.
* `size()`, `empty()` and `full()`
* copy/move operations
* `bool try_push_for(T const &, std::chrono::duration)` - The same as `try_push`, but if the operation would block longer than the given duration it returns `false` too. The operation is not performed then.
* `bool try_pop_for(T &, std::chrono::duration)` - The same as `try_pop`, but if the operation would block longer than the given duration it returns `false` too. The operation is not performed then.

In order to avoid duplicating the whole implementation of `BoundedBuffer` you should write `BoundedQueue` as a wrapper for `BoundedBuffer` and delegate the functionality of the queue to it.

* Use strategized locking for your `BoundedQueue`. The used mutex and condition variable types shall be template parameters. Use `std::mutex` and `std::condition_variable` as default arguments.
* Make sure that exceptions do not keep the mutex locked. Use an appropriate standard wrapper type.

For your convenience, test cases for BoundedQueue are provided [here](BoundedQueueTests.zip)

## Theory Questions on BoundedQueue

* Why does it not make sense to use `front()` and `back()` member functions for a thread-safe container?
* Why is it difficult to provide iterators for a thread-safe container?
* Why is `BoundedQueue::pop()` returning a `T` by value compared to the `void` return type of `BoundedBuffer::pop()`.
* Does supporting copy and move operations really make sense for a BoundedQueue? What would be a more appropriate Manager category for it, since it is intended to be shared across threads by reference?


## Optional - CVU Student Critique 
In one of the past [ACCU cvu magazines](https://accu.org/journals/nonmembers/cvu_issue_neutered/) the following problem was posted:

Can you help the student and analyze their code and correct the bugs?

"I wanted to learn a bit about C++ threading to I tried writing a thread pool example. But it sometimes crashes - I've managed to get it down to a small example. Sometimes I get what I expected as output, for example: 
```
Worker done
Worker done
Ending thread #2
Ending thread #0
Worker done
Ending thread #1
Worker done
Ending thread #3
Worker done
All done
```

But other times I get a failure, for example:

```
Worker done
Ending thread #0
Worker done
Awaiting thread #1
Worker done
W
<crash>
```

I'm not sure what to do next - can you help? It is sufficient to recognize the issues, you don't need to solve them.

```cpp
#include <algorithm>
using namespace std;
#include <array>
#include <chrono>
using namespace chrono;
#include <cstdlib>
#include <iostream>
#include <thread>

static const int POOL_SIZE = 4;

// Allow up to 4 active threads
array<thread, POOL_SIZE> pool;

// Example 'worker' -- would in practice
// perform some, potentially slow, calculation
void worker()
{
  this_thread::sleep_for(
    milliseconds(rand() % 1000));


  cout << "Worker done\n";
}

// Launch the thread functoid 't' in a new
// thread, if there's room for one
template <typename T>
bool launch(T t)
{
  auto it = find_if(pool.begin(), pool.end(),
    [](thread const &thr)
    { return thr.get_id() == thread::id(); }
  );
  if (it == pool.end())
  {
    // everyone is busy
    return false;
  }
  *it = thread([=]()
  {
    t();
    thread self;
    swap(*it, self);
    self.detach();
    cout << "Ending thread #"
      << (it - pool.begin()) << "\n";
  });
  return true;
}

int main()
{
  while (launch(worker))
  {}

  // And run one in this thread
  // as an example of what we do
  // when the pool is full
  worker();

  for (auto & it : pool)
  {
    thread thread;
    swap(thread, it);
    if (thread.joinable())
    {
      cout << "Awaiting thread #"
        << (&it - &*pool.begin()) << "\n";
      thread.join();
    }
  }
  cout << "All done\n";
}
```
