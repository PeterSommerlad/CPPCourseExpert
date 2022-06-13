#ifndef DYNARRAY_H_
#define DYNARRAY_H_

#include <initializer_list>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

template<typename T>
class DynArray {
    using Container = std::vector<T>;
    Container values;

public:
    using size_type = typename Container::size_type;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using reverse_iterator = typename Container::reverse_iterator;
    using const_reverse_iterator = typename Container::const_reverse_iterator;
    using index_type = std::make_signed_t<size_type>;

    DynArray() = default;

    DynArray(std::initializer_list<T> list) :
            values { list } {
    }

    template<typename ITER>
    DynArray(ITER b, ITER e) :
            values(b, e) {
    }

    explicit DynArray(size_type n, T const &val = T { }) :
            values(n, val) {
    }
    [[nodiscard]]
    size_type size() const {
        return values.size();
    }
    [[nodiscard]]
    bool empty() const {
        return values.empty();
    }
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
        return values.at(adjust_index(index));
    }
    [[nodiscard]]
    T const& at(index_type index) const & {
        return values.at(adjust_index(index));
    }

    void push_back(T const &t) & {
        values.push_back(t);
    }
    [[nodiscard]]
    T const& front() const & {
        throw_if_empty();
        return values.front();
    }
    [[nodiscard]]
    T& front() & {
        throw_if_empty();
        return values.front();
    }
    [[nodiscard]]
    T const& back() const & {
        throw_if_empty();
        return values.back();
    }
    [[nodiscard]]
    T& back() & {
        throw_if_empty();
        return values.back();
    }

    //Sol CPlA Ex02: Implementation of the pop_back() function returning std::optional<T>
    std::optional<T> pop_back() & {
        if (empty()) {
            return {};
        }
        std::optional<T> popped_value = std::move(values.back()); //std::move to prevent unnecessary copy
        values.pop_back();
        return popped_value;
    }
    [[nodiscard]]
    iterator begin() & {
        return values.begin();
    }
    [[nodiscard]]
    iterator end() & {
        return values.end();
    }

    [[nodiscard]]
    const_iterator begin() const & {
        return values.begin();
    }

    [[nodiscard]]
    const_iterator end() const & {
        return values.end();
    }

    [[nodiscard]]
    reverse_iterator rbegin() & {
        return values.rbegin();
    }

    reverse_iterator rend() & {
        return values.rend();
    }

    const_reverse_iterator rbegin() const & {
        return values.rbegin();
    }

    const_reverse_iterator rend() const & {
        return values.rend();
    }

    const_iterator cbegin() const & {
        return values.cbegin();
    }

    const_iterator cend() const & {
        return values.cend();
    }

    const_reverse_iterator crbegin() const & {
        return values.crbegin();
    }

    const_reverse_iterator crend() const & {
        return values.crend();
    }

    void resize(size_type newsize) & {
        values.resize(newsize);
    }
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

// not needed for C++17 onwards due to CTAD
template<typename T>
[[nodiscard]]
DynArray<T> make_dynArray(std::initializer_list<T> l) {
    return DynArray<T>(l);
}

#endif /* DYNARRAY_H_ */
