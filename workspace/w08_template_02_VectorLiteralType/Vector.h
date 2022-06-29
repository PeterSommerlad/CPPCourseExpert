#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstddef>
#include <type_traits>

template<typename T, typename ...U>
constexpr bool are_all_same = std::conjunction_v<std::is_same<T, std::remove_cv_t<std::remove_reference_t<U>>>...>;


template<typename T, std::size_t N>
class Vector {

};


#endif /* VECTOR_H_ */
