#include <type_traits>
#include <cmath>
#include <iostream>

constexpr double power(double b, unsigned x)
{
    if (std::is_constant_evaluated()) {
        double r = 1.0;
        while (x != 0) {
            if (x & 1) r *= b;
            x /= 2;
            b *= b;
        }
        return r;
    } else {
        return std::pow(b, static_cast<double>(x));
    }
}

int main()
{
    // A constant-expression context
    constexpr double kilo = power(10.0, 100);
    unsigned n = 3;
    // Not a constant expression, because n cannot be converted to an rvalue
    // in a constant-expression context
    // Equivalent to std::pow(10.0, double(n))
    double mucho = power(10.0, n);

    std::cout << kilo << " " << mucho << "\n"; // (3)
}
