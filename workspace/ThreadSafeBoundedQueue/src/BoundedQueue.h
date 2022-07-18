#ifndef BOUNDEDQUEUE_H_
#define BOUNDEDQUEUE_H_

#include "BoundedBuffer.h"

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <utility>

using heap_non_default::BoundedBuffer;

//TODO: Add template signature
template<typename T, typename MUTEX=std::mutex, typename CONDVAR=std::condition_variable>
struct BoundedQueue {

	//TODO: Add member types
    using size_type = BoundedBuffer<T>::size_type;

	//TODO: Add constructors
    explicit
    BoundedQueue(size_type sz)
    : buffer{sz}{}
    BoundedQueue(BoundedQueue const &other)
    :buffer{(std::scoped_lock{other.mutex},other.buffer)}
    {}
    BoundedQueue(BoundedQueue &&other)
    :buffer{(std::scoped_lock{other.mutex},std::move(other.buffer))}
    {}

    BoundedQueue & operator=(BoundedQueue const &other){
        if (this != &other){
            std::scoped_lock guard{mutex,other.mutex};
            buffer = other.buffer;
            if (not buffer.full()) is_not_full.notify_all();
            if (not buffer.empty()) is_not_full.notify_all();
        }
        return *this;
    }
    BoundedQueue & operator=(BoundedQueue &&other){
        if (this != &other){
            std::scoped_lock const guard{mutex,other.mutex};
            buffer = std::move(other.buffer);
            if (not buffer.full()) is_not_full.notify_all();
            if (not buffer.empty()) is_not_full.notify_all();
            other.is_not_full.notify_all(); // move assignment empties
       }
        return *this;
    }

	bool empty() const {
        std::scoped_lock const guard(mutex);
		return buffer.empty();
	}

	bool full() const {
        std::scoped_lock const guard(mutex);
		return buffer.full();
	}

	size_type size() const {
        std::scoped_lock const guard(mutex);
		return buffer.size();
	}

	void push(T const & element) {
        std::unique_lock guard(mutex);
        is_not_full.wait(guard,[this](){ return !buffer.full();});
	    buffer.push(element);
	    is_not_empty.notify_all();
	}

	void push(T && element) {
        std::unique_lock guard(mutex);
        is_not_full.wait(guard,[this](){ return !buffer.full();});
        buffer.push(std::move(element));
        is_not_empty.notify_all();

	}

	bool try_push(T const & element) {
        std::scoped_lock const guard(mutex);
        if (buffer.full()){
            return false;
        }
        buffer.push(element);
        is_not_empty.notify_all();
		return true;
	}

	template <typename Rep, typename Period>
	bool try_push_for(T const & element, std::chrono::duration<Rep, Period> duration) {
        std::unique_lock guard(mutex);
        if (is_not_full.wait_for(guard,duration,[this](){ return !buffer.full();})){
            buffer.push(element);
            is_not_empty.notify_all();
            return true;
        }
		return false;
	}

	T pop() {
        std::unique_lock guard(mutex);
        is_not_empty.wait(guard,[this](){ return !buffer.empty();});
        auto result = std::move(buffer.front());
        buffer.pop();
        is_not_full.notify_all();
		return result;
	}

	bool try_pop(T & ret) {
        std::scoped_lock guard(mutex);
        if (buffer.empty()) return false;
        ret = std::move(buffer.front());
        buffer.pop();
        is_not_full.notify_all();
        return true;
	}

	template <typename Rep, typename Period>
	bool try_pop_for(T & ret, std::chrono::duration<Rep, Period> duration) {
	    std::unique_lock guard(mutex);
	    if(is_not_empty.wait_for(guard,duration,[this](){ return !buffer.empty();})){
	        ret = std::move(buffer.front());
	        buffer.pop();
	        is_not_full.notify_all();
	        return true;
	    }
	    return false;
	}

	void swap(BoundedQueue & other)  {
        std::scoped_lock guard{mutex,other.mutex};
        buffer.swap(other.buffer);
        if (not buffer.full()) is_not_full.notify_all();
        if (not buffer.empty()) is_not_empty.notify_all();
        if (not other.buffer.full()) other.is_not_full.notify_all();
        if (not other.buffer.empty()) other.is_not_empty.notify_all();
	}

private:
	BoundedBuffer<T> buffer;
	//TODO: Add mutex
	mutable MUTEX mutex{};
    CONDVAR is_not_full{};
    CONDVAR is_not_empty{};
};


#endif /* BOUNDEDQUEUE_H_ */
