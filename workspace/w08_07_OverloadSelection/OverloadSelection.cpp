unsigned increment(unsigned i) {
  return i++;
}
template<typename T>
T increment(T value) {
  return value.increment();
}
int main() {
  return increment(42);
}
