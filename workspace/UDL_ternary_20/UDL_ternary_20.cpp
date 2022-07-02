#include<iostream>
#include<cstddef>
namespace ternary {
namespace _impl {
consteval unsigned long long
three_to(std::size_t power) {
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
constexpr unsigned long long value_of(char c) {
  return static_cast<unsigned long long>(c - '0');
}
template<std::same_as<char> ...ARGS>
constexpr unsigned long long
value_of(char c, ARGS...digits){
  static_assert(sizeof...(digits));
  return value_of(c)*three_to(sizeof...(digits))
         + value_of(digits...);
}
}
template<char ...Digits>
consteval unsigned long long operator"" _3()
requires (_impl::is_ternary_digit(Digits) && ...)
{
   return _impl::value_of(Digits...);
}
}
int main(int argc, char **argv) {
	using namespace ternary;
	std::cout << "11_ternary is " << 11_3 << '\n';
	std::cout << "02_ternary is " << 02_3 << '\n';
	std::cout << "120_ternary is " << 120_3 << '\n';
//	std::cout << "14_ternary is " << 14_3 << '\n'; // compile-error
}
