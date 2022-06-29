#include <array>
#include <cmath>

template <typename T>
class Vec3d {
	std::array<T, 3> values{};
public:
	constexpr Vec3d(T x, T y, T z)
		: values{x, y, z}{}
	constexpr T length() const {
		auto sumsq = x() * x() + y() * y() + z() * z();
		return std::sqrt(sumsq);
	}
	constexpr T & x() & {
		return values[0];
	}
	constexpr T const & x() const & {
		return values[0];
	}
	constexpr T & y() & {
		return values[1];
	}
	constexpr T const & y() const & {
		return values[1];
	}
	constexpr T & z() & {
		return values[2];
	}
	constexpr T const & z() const & {
		return values[2];
	}
};

constexpr bool
doubleEqual(double first,
            double second,
            double epsilon = 0.0001) {
	return std::abs(first - second) < epsilon;
}
constexpr Vec3d<double> create() {
	Vec3d<double> v{1.0, 1.0, 1.0};
	v.x() = 2.0;
	return v;
}
constexpr auto v = create();
static_assert(doubleEqual(v.length(), 2.4495));
int main() {
	//v.x() = 1.0;
	auto v2 = create();
	v2.x() = 2.0;
}
