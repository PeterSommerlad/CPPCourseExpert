#include "ThreadSafeQueue.h"
#include<iostream>
#include <syncstream>
#include<string>

int main() {
  using namespace std::this_thread;
  using namespace std::chrono_literals;
  TSQ::ThreadsafeQueue<int> queue { };
  std::thread prod1 { [&] {
    sleep_for(10ms); // demonstration only
    for (int j = 0; j < 10; ++j) {
      queue.push(j);
      yield();
      sleep_for(1ms);
    }
  } };
  std::thread prod2 { [&] {
    sleep_for(9ms); // demonstration only
    for (int i = 0; i < 10; ++i) {
      queue.push(i * 11);
      yield();
      sleep_for(1ms);
    }
  } };
  std::thread cons { [&] {
    sleep_for(15ms); // demonstration only
    do {
      std::osyncstream { std::cout } << "consume: " << queue.pop() << '\n';
      yield();
    } while (!queue.empty());
  } };
  prod1.join(), prod2.join(), cons.join();
  std::cout << "non-processed elements:\n";
  while (!queue.empty()) {
    std::cout << queue.pop() << '\n';
  }
}
