#include <stdexcept>

constexpr void throwIfZero(int value) {
  if (value == 0) {
    throw std::logic_error{""};
  }
}

constexpr int divide(int n, int d) {
  throwIfZero(d);
  return n / d;
}

constexpr auto five = divide(120, 24);
constexpr auto failure = divide(120, 0);

int main() {

}
