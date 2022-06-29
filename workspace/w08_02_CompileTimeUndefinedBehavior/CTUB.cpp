#include <iostream>

constexpr int divide(int n, int d) {
  return n / d;
}

constexpr auto surprise = divide(0, 0);

int main() {
  std::cout << surprise;
}
