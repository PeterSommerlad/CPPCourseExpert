#include <cstring>
#include <iostream>
#include <cstddef>

namespace ternary {
namespace _impl {

consteval unsigned long long three_to(std::size_t power) {
  auto result{1ULL};
  while(power>0) {
    result*=3;
    --power;
  }
	return result;
}

constexpr bool is_ternary_digit(char c) {
	return c == '0' || c == '1' || c == '2';
}

constexpr unsigned value_of(char c) {
	return c - '0';
}

// forward declaration for variable template without definition
template<char ...Digits>
extern unsigned long long ternary_value;
template<char ...Digits>
constexpr unsigned long long
ternary_value<'0', Digits...> { ternary_value<Digits...> };
template<char ...Digits>
constexpr unsigned long long
ternary_value<'1', Digits...> {
  1 * three_to(sizeof ...(Digits)) + ternary_value<Digits...>
};
template<char ...Digits>
constexpr unsigned long long
ternary_value<'2', Digits...> {
  2 * three_to(sizeof ...(Digits)) + ternary_value<Digits...>
};
template<>
constexpr unsigned long long
ternary_value<>{0};
}

template<char ...Digits>
consteval unsigned long long operator"" _ternary() {
	return _impl::ternary_value<Digits...>;
}
}

int main(int argc, char **argv) {
	using namespace ternary;
	std::cout << "11_ternary is " << 11_ternary << '\n';
	std::cout << "02_ternary is " << 02_ternary << '\n';
	std::cout << "120_ternary is " << 120_ternary << '\n';
//	std::cout << "14_ternary is " << 14_ternary << '\n'; // compile-error
}
