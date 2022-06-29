#ifndef SRC_WRAPPER_VALUE_H_
#define SRC_WRAPPER_VALUE_H_

#include <utility>

namespace wrap_value {

template<typename T>
struct wrapper{
  wrapper() = default;
  explicit wrapper(T x)
  :value{std::move(x)}{}
  T value;
  void replace(T x)& {
    value = std::move(x);
  }
};


}



#endif /* SRC_WRAPPER_VALUE_H_ */
