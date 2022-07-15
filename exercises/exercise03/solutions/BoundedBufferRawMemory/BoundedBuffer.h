#ifndef BOUNDEDBUFFER_H_
#define BOUNDEDBUFFER_H_
#include <array>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

namespace heap_non_default {

template<typename T>
struct BoundedBuffer {
using size_type = size_t;

explicit
BoundedBuffer(size_type max)
:maxsz{checkForZero(max)}
,elements{std::make_unique<std::byte[]>(sizeof(T)*maxsz)}
{}

~BoundedBuffer() {
    destroyAllElements();
}
BoundedBuffer(BoundedBuffer &&other) noexcept
: BoundedBuffer{other.maxsz} {
    this->swap(other);
}
BoundedBuffer& operator=(BoundedBuffer &&other) & noexcept {
    destroyAllElements();
    this->swap(other);
    return *this;
}
BoundedBuffer(BoundedBuffer const &other)
: maxsz{checkForZero(other.maxsz)}
,elements{std::make_unique<std::byte[]>(sizeof(T)*maxsz)}
{
    append_elements(other);
}
BoundedBuffer& operator=(BoundedBuffer const &other){
    destroyAllElements();
    if (maxsz != other.maxsz){
        maxsz = other.maxsz;
        elements = std::make_unique<std::byte[]>(sizeof(T)*maxsz);
    }
    append_elements(other);
    return *this;
}
bool empty() const { return size() == 0; }
bool full() const { return size() == maxsz; }
size_type size() const { return count; }
T& front() & {
    throwOnEmpty();
    return element_at(first);
}
T const& front() const &{
    throwOnEmpty();
    return element_at(first);
}
T& back() &{
    throwOnEmpty();
    return element_at(back_index());
}
T const & back() const &{
    throwOnEmpty();
    return element_at(back_index());
}
void pop() &  {
    throwOnEmpty();
    //front().~T();
    std::destroy_at<T>(&element_at(first));
    first = (first + 1) % maxsz;
    --count;
}
void push(T const &element) & {
    if (full()) throw std::logic_error{"buffer full"};
    auto pos = (first+count) % maxsz;
    //std::ignore = ::new(element_address(pos)) T{element};
    std::construct_at<T>(element_address(pos),  element);
    ++count;
}
void push(T  && element) & {
    if (full()) throw std::logic_error{"buffer full"};
    auto pos = (first+count) % maxsz;
    //std::ignore = ::new(element_address(pos)) T{std::move(element)};
    std::construct_at<T>(element_address(pos), std::move(element) );
    ++count;
}

template <typename ...Params>
void push_emplace(Params&& ...ps) & {
    if (full()) throw std::logic_error{"buffer full"};
    auto pos = (first+count) % maxsz;
    //std::ignore = ::new(element_address(pos)) T{std::forward<Params>(ps)...};
    std::construct_at<T>(element_address(pos), std::forward<Params>(ps)... );
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
size_type maxsz {1};
std::unique_ptr<std::byte[]> elements{};

T* element_address(size_type index) const {
    if (index >= maxsz) throw std::out_of_range{"error in BoundedBuffer"};
    size_type const byte_index = index * sizeof(T);
    return reinterpret_cast<T*>(&elements[byte_index]);
}

T & element_at(size_type index){
    return *(element_address(index));
}
T const & element_at(size_type index)const{
    return *const_cast<T const *>(element_address(index));
}

size_type checkForZero(size_type max){
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
void destroyAllElements() noexcept {
    while(! empty()){
        pop();
    }
}
void append_elements(BoundedBuffer const &other){
    for(size_t index=0; index < other.size(); ++index){
        this->push(other.element_at((other.first+index)%other.maxsz));
    }
}

};

}
#endif /* BOUNDEDBUFFER_H_ */
