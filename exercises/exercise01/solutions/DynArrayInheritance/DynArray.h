#ifndef DYNARRAY_H_
#define DYNARRAY_H_

#include <initializer_list>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

template<typename T>
class DynArray : std::vector<T> {
    using Base = std::vector<T>;

public:
    using size_type = typename Base::size_type;
    using iterator = typename Base::iterator;
    using const_iterator = typename Base::const_iterator;
    using reverse_iterator = typename Base::reverse_iterator;
    using const_reverse_iterator = typename Base::const_reverse_iterator;
    using index_type = std::make_signed_t<size_type>;

    using std::vector<T>::vector;
    using Base::size;
    using Base::empty;
    [[nodiscard]]
    T& operator[](index_type index) & {
        return at(index);
    }

    [[nodiscard]]
    T const& operator[](index_type index) const & {
        return at(index);
    }

    [[nodiscard]]
    T& at(index_type index) & {
        return Base::at(adjust_index(index));
    }
    [[nodiscard]]
    T const& at(index_type index) const & {
        return Base::at(adjust_index(index));
    }
    using Base::push_back;
    [[nodiscard]]
    T const& front() const & {
        throw_if_empty();
        return Base::front();
    }
    [[nodiscard]]
    T& front() & {
        throw_if_empty();
        return Base::front();
    }
    [[nodiscard]]
    T const& back() const & {
        throw_if_empty();
        return Base::back();
    }
    [[nodiscard]]
    T& back() & {
        throw_if_empty();
        return Base::back();
    }

    //Sol CPlA Ex02: Implementation of the pop_back() function returning std::optional<T>
    std::optional<T> pop_back() & {
        if (empty()) {
            return {};
        }
        std::optional<T> popped_value = std::move(back()); //std::move to prevent unnecessary copy
        Base::pop_back();
        return popped_value;
    }
    using Base::begin;
    using Base::end;
    using Base::rbegin;
    using Base::rend;
    using Base::cbegin;
    using Base::cend;
    using Base::crbegin;
    using Base::crend;
    using Base::resize;
#ifndef __clang__
    DynArray(std::initializer_list<T> l)
    : Base::vector(l){}
#endif
private:
    void throw_if_empty() const {
        if (empty())
            throw std::out_of_range { "DynArray empty" };
    }
    size_type adjust_index(index_type index) const {
        if (index < 0){
            return size() + static_cast<size_type>(index); // modulo operation, two's complement signed integer
        } else {
            return static_cast<size_type>(index);
        }
    }

};
#ifdef __clang__
template<typename T>
DynArray(std::initializer_list<T>) -> DynArray<T>;
#endif /* not preferred by gcc 11 in C++17 mode */
template<typename T>
DynArray(size_t, T const &) -> DynArray<T>;

// not needed for C++17 onwards due to CTAD
template<typename T>
[[nodiscard]]
DynArray<T> make_dynArray(std::initializer_list<T> l) {
    return DynArray<T>(l);
}

#endif /* DYNARRAY_H_ */
