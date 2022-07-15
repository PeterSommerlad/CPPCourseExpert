#ifndef VECTOR_H_
#define VECTOR_H_

#include <array>
#include <cmath>
#include <cstddef>
#include <numeric>
#include <type_traits>
#include <utility>
#include <ostream>

template<typename T, typename ...U>
constexpr bool are_all_same = (std::is_same_v<T,std::remove_cv_t<std::remove_reference_t<U>>> && ...);
// std::conjunction_v<std::is_same<T, std::remove_cv_t<std::remove_reference_t<U>>>...>;


template<typename T, std::size_t N>
class Vector {
	std::array<T, N> values { };
public:
	template<typename ...U, typename = std::enable_if_t<are_all_same<T, U...>>>
	explicit constexpr Vector(U &&... u) :
			values { std::forward<U>(u)... } {
	}

	constexpr T const & operator[](size_t index) const & {
		return values.at(index);
	}

	constexpr T & operator[](size_t index) & {
		return values.at(index);
	}

	constexpr T length() const {
	    return std::sqrt(std::reduce(begin(values),end(values),T{},[](auto s, auto e){ return s + e*e;}));
	    // C++17: reduce not yet constexpr
//		T sum{};
//		for (auto index = 0u; index < N; index++) {
//			sum += values[index] * values[index];
//		}
//		return std::sqrt(sum);
	}

	constexpr T innerProduct(Vector const & other) const {

		return std::inner_product(begin(values),end(values),begin(other.values),T{});
		// C++17:
//        T sum{};
//        for (auto index = 0u; index < N; index++) {
//            sum += values[index] * other[index];
//        }
//        return sum;

	}

	constexpr bool operator==(Vector const & other) const = default;
//	{   // alt C++20:
//	    return values == other.values;
//	    // C++17:
////		for (size_t index = 0u; index < N; index++) {
////			if ((*this)[index] != other[index]) {
////				return false;
////			}
////		}
////		return true;
//	}
//
//	constexpr bool operator!=(Vector const & other) const {
//		return !(*this == other);
//	}
};

template <typename T, std::size_t N>
std::ostream & operator<<(std::ostream & out, Vector<T, N> const & v) {
	out << '(';
	for (size_t index = 0u; index < N; index++) {
		if (index > 0u) {
			out << ", ";
		}
		out << v[index];
	}
	out << ')';
	return out;
}


template <typename Head, typename...U>
Vector(Head, U ...) -> Vector<Head, sizeof...(U) + 1>;

#endif /* VECTOR_H_ */
