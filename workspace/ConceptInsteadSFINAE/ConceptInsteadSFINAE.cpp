#include <type_traits>
#include <concepts>

unsigned increment(unsigned i) {
  return i++;
}

//template<typename T>
//auto increment(T value)
//requires requires (T x) { {x.increment()} -> std::same_as<T>;}
//{
//  return value.increment();
//}

template<typename T>
concept incrementable = requires (T x) { {x.increment()} -> std::same_as<T>;};

//template<typename T>
//auto increment(T value)
//requires incrementable<T>
//{
//  return value.increment();
//}
template<typename T>
requires incrementable<T>
auto increment(T value)
{
  return value.increment();
}


//auto increment(incrementable auto value){
//  return value.increment();
//}

template<std::integral auto by>
auto increment_by(std::integral auto value)
{
  return value+=by;
}

struct counter {
  int count;
  auto increment() {  ++count; return *this; }
};


int main() {
  counter c{};
  increment(c);

  return increment(42) + increment_by<2>(-42);
}
