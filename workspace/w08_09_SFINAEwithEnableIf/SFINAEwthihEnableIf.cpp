#include <type_traits>

unsigned increment(unsigned i) {
  return i++;
}

template<typename T>
std::enable_if_t<std::is_class<T>::value, T> increment(T value) {
  return value.increment();
}

//template<typename T>
//T increment(std::enable_if_t<std::is_class<T>::value, T> value) {
//  return value.increment();
//}

//template<typename T, typename = std::enable_if_t<std::is_class<T>::value, void>>
//T increment(T value) {
//  return value.increment();
//}


int main() {
  return increment(42);
}
