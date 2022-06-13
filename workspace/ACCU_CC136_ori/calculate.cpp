#include "expression.h"
#include <iostream>

int main() {
  double result, rhs;
  while (std::cin >> result) {
    for (;;) {
      char ch;
      if (std::cin >> ch) {
        if (ch == '=') {
          std::cout << "Result: " << result
                    << '\n';
          break;
        } else {
          if (std::cin >> rhs) {
            result = apply(
                result, (operation)ch, rhs);
          } else {
            break;
          }
        }
      } else {
        break;
      }
    }
  }
}
