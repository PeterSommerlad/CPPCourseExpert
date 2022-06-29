#include "PetersonMutexAtomics.h"
#include "PetersonMutexVolatile.h"
#include <thread>
#include <ostream>
#include <iostream>

using MutexType = PetersonMutexAtomics;
//using MutexType = PetersonMutexVolatile;

int main(int argc, char **argv) {
	while(true) {
		unsigned const NofRounds { 100000 };
		unsigned counter { 0 };
		MutexType mutex { };

		std::thread t0 { [&]() {
			for (auto i = 0u; i < NofRounds; i++) {
				mutex.thread0Lock();
				counter++;
				mutex.thread0Unlock();
			}
		} };

		std::thread t1 { [&]() {
			for (auto i = 0u; i < NofRounds; i++) {
				mutex.thread1Lock();
				counter--;
				mutex.thread1Unlock();
			}
		} };
		t0.join();
		t1.join();

		if (counter != 0) {
			std::cout << "Expected value 0 but was " << counter << std::endl;
			return -1;
		} else {
			std::cout << "Completed successfully!" << std::endl;
		}
	}
}