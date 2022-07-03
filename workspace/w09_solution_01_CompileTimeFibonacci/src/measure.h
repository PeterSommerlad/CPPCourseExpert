#ifndef MEASURE_H_
#define MEASURE_H_

#include <chrono>
#include <functional>
#include <ostream>
#include <utility>

template <typename F>
auto measure(F && f) {
	auto const start = std::chrono::high_resolution_clock::now();
	std::invoke(std::forward<F>(f));
	auto const end = std::chrono::high_resolution_clock::now();
	auto const duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	return duration;
}

#endif /* MEASURE_H_ */
