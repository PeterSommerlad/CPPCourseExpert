#ifndef SRC_WRAPPER_RAW_NONMOVABLE_H_
#define SRC_WRAPPER_RAW_NONMOVABLE_H_

#include<utility>
#include<memory>
#include<array>
#include<cstddef>
#include<stdexcept>

namespace wrap_raw_nonmovable {

template<typename T>
struct wrapper{
    //construct in-place
    template<typename...PARAMS>
    explicit wrapper(PARAMS &&...args)
    : engaged{[this](auto&& ...arg){
     auto ptr = adr();
#if __cplusplus >= 202002L
      ptr = std::construct_at(ptr,std::forward<PARAMS>(arg)...);
#else
      ptr =  new(ptr) T{std::forward<PARAMS>(arg)...};
#endif
      return true;
    }(std::forward<PARAMS>(args)...)}{ }
    ~wrapper(){
      if (engaged){
#if __cplusplus >= 201703L
        std::destroy_at(adr());
#else
        value().~T();
#endif
      }
    }
    T& value() & {
      if (!engaged) throw std::logic_error("non-engaged wrapper");
      return *adr();
    }
    T const & value() const & {
      if (!engaged) throw std::logic_error("non-engaged wrapper");
      return *
#if __cplusplus >= 201703L
          std::launder
#endif
          (reinterpret_cast<T const *>(value_store.data()));

    }
    void replace(T const & x) &
#if __cplusplus >= 202002L
    requires std::is_copy_assignable_v<T>
#endif
    {
      if (engaged){
       value() = x;
      } else {
        auto ptr = adr();
   #if __cplusplus >= 202002L
         ptr = std::construct_at(ptr,x);
   #else
         ptr =  new(ptr) T{x};
   #endif
         engaged=true;
      }
    }

    void replace(T&& x) &
#if __cplusplus >= 202002L
    requires std::is_move_assignable_v<T>
#endif
    {
      if (engaged){
        value() = std::move(x);
      } else {
        auto ptr = adr();
   #if __cplusplus >= 202002L
         ptr = std::construct_at(ptr,std::move(x));
   #else
         ptr =  new(ptr) T{std::move(x)};
   #endif
         engaged=true;
      }
    }
    template<typename...PARAMS>
    void replace(PARAMS &&...args) &
#if __cplusplus >= 202002L
    requires (std::is_nothrow_constructible_v<T,PARAMS...>)
#endif
    {
      auto ptr = adr();
      // cannot assign, caution not exception safe!
#if __cplusplus >= 202002L
      if (engaged) std::destroy_at(ptr);
      std::construct_at(ptr,std::forward<PARAMS>(args)...);
#else
      // destroy existing object
      if (engaged) ptr->~T();
      // construct new object
      new(ptr)T(std::forward<PARAMS>(args)...);
#endif
      engaged=true;
    }
    void forget()& noexcept {
      if (engaged){
#if __cplusplus >= 201700L
        std::destroy_at(std::addressof(value()));
#else
        value().~T();
#endif
        engaged=false;
      }
    }
private:
#if __cplusplus >= 201703L
    using byte=std::byte;
#else
    using byte= unsigned char;
#endif
    alignas(T) std::array<byte,sizeof(T)> value_store;
    T * adr() {
      return
#if __cplusplus >= 201703L
          std::launder
#endif
          (reinterpret_cast<T*>(value_store.data()));
    }
    bool engaged{};

};


template<typename FUNC, typename T>
auto wrapit(FUNC &&f,T&& arg){
  //f(arg);
  f(std::forward<T>(arg));
}

}



#endif /* SRC_WRAPPER_RAW_NONMOVABLE_H_ */
