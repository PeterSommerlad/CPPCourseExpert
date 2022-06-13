#ifndef BOUNDEDBUFFER_H_
#define BOUNDEDBUFFER_H_
#include <array>
#include <stdexcept>
#include <utility>

template<typename T, size_t N>
struct BoundedBuffer {
using value_type = T;
using reference = T&;
using const_reference = T const &;
using container_type = std::array<T,N>;
using size_type = container_type::size_type;

bool empty() const { return size() == 0; }
bool full() const { return size() == N; }
size_type size() const { return count; }
reference front() & {
    throwOnEmpty();
    return elements[first];
}
const_reference front() const &{
    throwOnEmpty();
    return elements[first];
}
reference back() &{
    throwOnEmpty();
    return elements[back_index()];
}
const_reference back() const &{
    throwOnEmpty();
    return elements[back_index()];
}
void pop() & {
    throwOnEmpty();
    first = (first + 1) % N;
    --count;
}
void push(T const &element) & {
    if (full()) throw std::logic_error{"buffer full"};
    auto pos = (first+count) % N;
    elements[pos] = element;
    ++count;
}
void push(T  && element) & {
    if (full()) throw std::logic_error{"buffer full"};
    auto pos = (first+count) % N;
    elements[pos] = std::move(element);
    ++count;
}

private:
container_type elements{};
size_type first {0};
size_type count {0};
size_type back_index() const {
    return (first + count - 1) % N;
}
void throwOnEmpty() const {
    if (empty()) throw std::logic_error{"buffer empty"};
}

};


#endif /* BOUNDEDBUFFER_H_ */
