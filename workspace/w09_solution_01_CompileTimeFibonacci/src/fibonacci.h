#ifndef FIBONACCI_H_
#define FIBONACCI_H_

#include <array>
#include <cctype>
#include <stdexcept>


inline constexpr unsigned long long fibo(unsigned n) {
	if (n < 2) {
		return n;
	}
	return fibo(n - 1) + fibo(n - 2);
}

//template <unsigned long long n>
//constexpr auto fibo_v = fibo(n);

template <unsigned long long n>
constexpr auto fibo_v = (fibo_v<n-2>) + (fibo_v<n-1>);

template <>
constexpr auto fibo_v<0> = 0;

template <>
constexpr auto fibo_v<1> = 1;


inline constexpr unsigned long long operator"" _fibo(unsigned long long n) {
	return fibo(n);
}


template <std::size_t n>
inline constexpr auto fiboa() {
	std::array<unsigned long long, n> fibs{};
	for (auto index = 0u; index < n; index++) {
		fibs[index] = fibo(index);
	}
	return fibs;
}

template <std::size_t n>
constexpr auto fiboa_v = fiboa<n>();


namespace {
	constexpr inline unsigned parseDigit(char c) {
		if (!std::isdigit(c)) {
			throw std::invalid_argument{"c is not a digit"};
		}
		return c - '0';
	}

	template <char First, char...C>
	constexpr inline auto parseSize(unsigned long long previous = 0) {
		constexpr auto digitValue = parseDigit(First);
		auto result = previous + digitValue;
		if constexpr (sizeof...(C)) {
			return parseSize<C...>(result * 10);
		} else {
			return result;
		}
	}
}

template <char...C>
inline constexpr auto operator"" _fiboa() {
	constexpr auto size = parseSize<C...>();
	return fiboa_v<size>;
}


#endif /* FIBONACCI_H_ */
