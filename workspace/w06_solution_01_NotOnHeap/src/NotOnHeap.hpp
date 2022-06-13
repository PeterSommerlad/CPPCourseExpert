#ifndef NOTONHEAP_HPP_
#define NOTONHEAP_HPP_

#include <cstddef>
#include <new>


struct not_on_heap {
	bool valid() const {
		return true;
	}
    static void* operator new(std::size_t sz) {
    	throw std::bad_alloc{};
    }
    static void* operator new[](std::size_t sz){
    	throw std::bad_alloc{};
    }
    static void operator delete(void *ptr) noexcept  {
    	// do nothing, never called, but should come in pairs
    }
    static void operator delete[](void *ptr) noexcept {
    	// do nothing, never called, but should come in pairs
    }
};



#endif /* NOTONHEAP_HPP_ */
