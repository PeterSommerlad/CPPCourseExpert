#ifndef SRC_WRAPPER_H_
#define SRC_WRAPPER_H_

#include <utility>

namespace wrapit {

template<typename T>
struct wrapper{
  wrapper() = default;
  explicit wrapper(T const &x)
  :value{x}{}
  explicit wrapper(T&& x)
  :value{std::move(x)}{}
  T value;
  void replace(T const &x) & {
    value = x;
  }
  void replace(T &&x) & {
    value = std::move(x);
  }
};


}



#endif /* SRC_WRAPPER_H_ */
