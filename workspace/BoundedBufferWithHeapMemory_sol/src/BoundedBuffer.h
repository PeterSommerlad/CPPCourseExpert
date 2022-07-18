#ifndef BOUNDEDBUFFER_H_
#define BOUNDEDBUFFER_H_
#include <memory>
#include <stdexcept>
#include <utility>

namespace heap_memory {

template<typename T>
struct BoundedBuffer {
using size_type = size_t;

explicit
BoundedBuffer(size_type max)
    :maxsz{checkForZero(max)}
    ,elements{std::make_unique<T[]>(maxsz)}
    {}

~BoundedBuffer() noexcept = default; // OK
BoundedBuffer(BoundedBuffer const &other)
:BoundedBuffer{other.maxsz}
{
    append_elements(other);
}
BoundedBuffer& operator=(BoundedBuffer const &other) & {
  if (this!= &other){
    BoundedBuffer tmp{other};
    this->swap(tmp);
  }
  return *this;
}
BoundedBuffer(BoundedBuffer&& other) noexcept
{
    this->swap(other);
}
BoundedBuffer& operator=(BoundedBuffer&& other) & noexcept{
    first = 0;
    count = 0;
    maxsz = 0;
    elements.reset();
    this->swap(other);
    return *this;
}

bool empty() const { return size() == 0; }
bool full() const { return size() == maxsz; }
size_type size() const { return count; }
T& front() & {
    throwOnEmpty();
    return elements[first];
}
T const & front() const &{
    throwOnEmpty();
    return elements[first];
}
T& back() &{
    throwOnEmpty();
    return elements[back_index()];
}
T const & back() const &{
    throwOnEmpty();
    return elements[back_index()];
}
void pop() & {
    throwOnEmpty();
    first = (first + 1) % maxsz;
    --count;
}
void push(T const &element) & {
    if (full()) throw std::logic_error{"buffer full"};
    auto pos = (first+count) % maxsz;
    elements[pos] = element;
    ++count;
}
void push(T  && element) & {
    if (full()) throw std::logic_error{"buffer full"};
    auto pos = (first+count) % maxsz;
    elements[pos] = std::move(element);
    ++count;
}

void swap(BoundedBuffer  & other) & noexcept {
    using std::swap;
    swap(elements,other.elements);
    swap(first,other.first);
    swap(count,other.count);
    swap(maxsz,other.maxsz);
}

private:
size_type first {0};
size_type count {0};
size_type maxsz {0};
std::unique_ptr<T[]> elements{};

static size_type checkForZero(size_type max){
    if (0u == max){
        throw std::invalid_argument{"BoundedBuffer: zero size"};
    }
    return max;
}
size_type back_index() const {
    return (first + count - 1) % maxsz;
}
void throwOnEmpty() const {
    if (empty()) throw std::logic_error{"buffer empty"};
}
void append_elements(BoundedBuffer const &other) & {
    for(size_t index=0; index < other.size(); ++index){
        this->push(other.elements[(other.first+index)%other.maxsz]);
    }
}

};

template<typename T>
void swap(BoundedBuffer<T> & l, BoundedBuffer<T> &r) noexcept{
  l->swap(r);
}


}

#endif /* BOUNDEDBUFFER_H_ */
