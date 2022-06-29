#ifndef SRC_WRAPPER_NONMOVABLE_H_
#define SRC_WRAPPER_NONMOVABLE_H_

#include<utility>
#include <memory>

namespace wrap_nonmovable {

template<typename T>
struct wrapper{
    //construct in-place
    template<typename...PARAMS>
    explicit wrapper(PARAMS &&...args)
    :value(std::forward<PARAMS>(args)...){}
    T value;
    void replace(T const & x)
#if __cplusplus >= 202002L
    requires std::is_copy_assignable_v<T>
#endif
    {
      value = x;
    }

    void replace(T&& x)
#if __cplusplus >= 202002L
    requires std::is_move_assignable_v<T>
#endif
    {
      value = std::move(x);
    }
    template<typename...PARAMS>
    void replace(PARAMS &&...args)
#if __cplusplus >= 202002L
    requires (not std::is_move_assignable_v<T>)
#endif
    {
      // cannot assign, caution not exception safe!
#if __cplusplus >= 202002L
      std::destroy_at(&value);
      std::construct_at(&value,std::forward<PARAMS>(args)...);
#else
      // destroy existing object
      value.~T();
      // construct new object
      new(&value)T(std::forward<PARAMS>(args)...);
#endif
    }
};


template<typename FUNC, typename T>
auto wrapit(FUNC &&f,T&& arg){
  //f(arg);
  f(std::forward<T>(arg));
}

}



#endif /* SRC_WRAPPER_NONMOVABLE_H_ */
