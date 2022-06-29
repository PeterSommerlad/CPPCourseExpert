#include <iostream>

constexpr auto factorial(unsigned n) {
  auto result = 1u;
  for (auto i = 2u; i <= n; i++) {
    result *= i;
  }
  return result;
}

constexpr void foo(int n) {
	if (n < 1) {
		new int{};
	}
}

constexpr auto factorialOf5 = factorial(5);

int main() {
  static_assert(factorialOf5 == 120);
  std::cout << factorial(5);
}
