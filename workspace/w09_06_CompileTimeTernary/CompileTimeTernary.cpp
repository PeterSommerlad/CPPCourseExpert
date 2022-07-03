#include<cstring>
#include<iostream>

#include <cstddef>

namespace ternary {
namespace _impl {



constexpr unsigned long long three_to(std::size_t power) {
	return power ? 3ull * three_to(power - 1) : 1ull;
}

constexpr bool is_ternary_digit(char c) {
	return c == '0' || c == '1' || c == '2';
}

template<char D>
constexpr unsigned value_of() {
	static_assert(is_ternary_digit(D), "Digits of ternary must be 0, 1 or 2");
	return D - '0';
}

template<char ...Digits>
extern unsigned long long ternary_value;

template<char D, char ...Digits>
constexpr unsigned long long ternary_value<D, Digits...> {
	value_of<D>() * three_to(sizeof ...(Digits)) + ternary_value<Digits...>
};

template<>
constexpr unsigned long long ternary_value<>{0};

}

template<char ...Digits>
constexpr unsigned long long operator"" _ternary() {
	return _impl::ternary_value<Digits...>; //C++14
}
}

int main(int argc, char **argv) {
	using namespace ternary;
	std::cout << "11_ternary is " << 11_ternary << '\n';
	std::cout << "02_ternary is " << 02_ternary << '\n';
	std::cout << "120_ternary is " << 120_ternary << '\n';
//	std::cout << "14_ternary is " << 14_ternary << '\n'; // compile-error
}
