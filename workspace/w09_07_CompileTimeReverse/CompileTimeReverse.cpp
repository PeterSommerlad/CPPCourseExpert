#include <tuple>
#include <utility>

//constexpr auto reverse(std::tuple<> const & nullary) {
//  return nullary;
//}
//
//template <typename T>
//constexpr auto reverse(std::tuple<T> const & unary) {
//  return unary;
//}
//
//template <typename First, typename Second>
//constexpr auto reverse(std::tuple<First, Second> const & binary) {
//  return std::make_tuple(std::get<1>(binary), std::get<0>(binary));
//}
//
//template <typename...Types>
//constexpr auto reverse(std::tuple<Types...> const & ternary) {
//  return std::make_tuple(std::get<2>(ternary),
//                         std::get<1>(ternary),
//                         std::get<0>(ternary));
//}

template <typename Tuple, size_t...Indices>
constexpr auto reverseImpl(Tuple const & nAry, std::index_sequence<Indices...>) {
  constexpr auto firstIndex = sizeof...(Indices) - 1;
  return std::make_tuple(std::get<firstIndex - Indices>(nAry)...);
}

template <typename...Types>
  constexpr auto reverse(std::tuple<Types...> const & nAry) {
  return reverseImpl(nAry, std::make_index_sequence<sizeof...(Types)>());
}



constexpr auto nullary = std::make_tuple();
constexpr auto reversedNullary = reverse(nullary);
static_assert(nullary == reversedNullary);

constexpr auto unary = std::make_tuple(1);
constexpr auto reversedUnary = reverse(unary);
static_assert(unary == reversedUnary);

constexpr auto binary = std::make_tuple("Hello", 5);
constexpr auto binaryReversed = reverse(binary);
static_assert(binaryReversed == std::make_tuple(5, "Hello"));

constexpr auto ternary = std::make_tuple("Hello", 5, 3.14);
constexpr auto ternaryReversed = reverse(ternary);
static_assert(ternaryReversed == std::make_tuple(3.14, 5, "Hello"));

constexpr auto quaternary = std::make_tuple("Hello", 5, 3.14, '*');
constexpr auto quaternaryReversed = reverse(quaternary);
static_assert(quaternaryReversed == std::make_tuple('*', 3.14, 5, "Hello"));



int main() {

}
