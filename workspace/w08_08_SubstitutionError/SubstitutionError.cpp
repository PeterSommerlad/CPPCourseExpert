unsigned increment(unsigned i) {
  return i++;
}
template<typename T>
auto increment(T value)
  -> decltype(value.increment()) {
  return value.increment();
}
int main() {
  return increment(42);
}
