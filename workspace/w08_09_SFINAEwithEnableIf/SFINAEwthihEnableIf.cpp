#include <type_traits>
#include <utility>

unsigned increment(unsigned i) {
  return i++;
}

//template<typename T>
//std::enable_if_t<std::is_class_v<T>, T> increment(T value) {
//  return value.increment();
//}
//template<typename T>
//auto increment(T value) -> std::enable_if_t<std::is_class_v<T>, T>  {
//  return value.increment();
//}
//template<typename T>
//auto increment(T value) -> decltype(value.increment())  {
//  return value.increment();
//}
//template<typename T>
//decltype(std::declval<T>().increment())  increment(T value) {
//  return value.increment();
//}
// doesn't work:
//template<typename T>
//T increment(std::enable_if_t<std::is_class_v<T>, T> value) {
//  return value.increment();
//}
//template<typename T>
//T increment(T value, std::enable_if_t<std::is_class_v<T>, bool> =false) {
//  return value.increment();
//}

template<typename T, typename = std::enable_if_t<std::is_class_v<T>, void>>
T increment(T value) {
  return value.increment();
}

struct counter {
  int count;
  auto increment() {  ++count; return *this; }
};


int main() {
  counter c{};
  increment(c);
  return increment(42);
}
