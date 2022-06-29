#include "ThreadSafeExchange.h"
#include<iostream>
#include <syncstream>
#include<thread>
#include<latch>
#include <ostream>
int main() {
  using namespace std::this_thread;
  using namespace std::chrono_literals;
  TSQ::ThreadsafeExchange<int> queue { };
  std::latch startit{3+1}; // we have 3 threads +main
  std::jthread prod1 { [&] (std::stop_token stop){
    startit.arrive_and_wait();
    for (int j = 0; !stop.stop_requested() &&  j < 10; ++j) {
      std::osyncstream {std::cout} << "produce: " << j << '\n';
      queue.try_push_for(j,1ms);
      yield();
    }
  } };
  std::jthread prod2 { [&] (std::stop_token stop) {
    startit.arrive_and_wait();
    for (int i = 1; !stop.stop_requested() &&i < 10; ++i) {
      std::osyncstream {std::cout} << "produce: " << i*11 << '\n';
      queue.try_push(i * 11);
      yield();
    }
  } };
  std::jthread cons { [&] (std::stop_token stop) {
    startit.arrive_and_wait();
    int count{0};
    while ( not stop.stop_requested() ) {
      std::osyncstream { std::cout } << "consuming: " << queue.pop() << '\n';
      ++count;
    }
    std::osyncstream { std::cout } << "consumed elts: " << count << '\n';
  } };
  sleep_for(10ms);
  std::cout << "Go go go..."<< std::endl;
  startit.arrive_and_wait(); // turn on
  sleep_for(40ms);
  auto success = cons.request_stop();
  queue.try_push(42); // unblock consumer on pop.
   success = prod2.request_stop() && success;
   success = prod1.request_stop() && success;
   if (success) cons.join();
  std::osyncstream{std::cout} << "stop-success: " << std::boolalpha << success << std::endl;

}
