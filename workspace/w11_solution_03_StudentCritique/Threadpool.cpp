#include <algorithm>
using namespace std;
#include <array>
#include <chrono>
using namespace chrono;
#include <cstdlib>
#include <iostream>
#include <thread>


/* Problems: Most access to pool elements needs to be locked. */


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
  auto it = find_if(pool.begin(), pool.end(), //Solution: This iteration is ok. The array has fixed size and the iterators can be used to specify the range without synchronization.
    [](thread const &thr)
    { return thr.get_id() == thread::id(); } //Solution: This access needs to be synchronized. Since the element "thr" might be changed in another thread.
  );
  if (it == pool.end()) //Solution: Ok
  {
    // everyone is busy
    return false;
  }
  *it = thread([=]() //Solution: This assignment to *it needs to be synchronized.
  {
    t();
    thread self;
    swap(*it, self); //Solution: This assignment to *it needs to be synchronized.
    self.detach(); //Solution: Ok
    cout << "Ending thread #"
      << (it - pool.begin()) << "\n"; //Solution: Ok
  });
  return true;
}

int main()
{
  while (launch(worker)) //Solution: Might loop infinitely!
  {}

  // And run one in this thread
  // as an example of what we do
  // when the pool is full
  worker();

  for (auto & it : pool) //Solution: Ok
  {
    thread thread;
    swap(thread, it); //Solution: This assignment to *it needs to be synchronized.
    if (thread.joinable()) //Solution: Ok
    {
      cout << "Awaiting thread #"
        << (&it - &*pool.begin()) << "\n"; //Solution: Ok
      thread.join(); //Solution: Ok
    }
  }
  cout << "All done\n";
}
