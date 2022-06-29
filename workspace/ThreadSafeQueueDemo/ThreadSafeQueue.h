#ifndef THREADSAFEEXCHANGE_H_
#define THREADSAFEEXCHANGE_H_


#include <condition_variable>
#include <mutex>
#include <queue>
namespace TSQ {
template<typename T, typename MUTEX=std::mutex>
struct ThreadsafeQueue {
    void push(T const & t) {
        std::scoped_lock const lk { mx };
        q.push(t);
        notEmpty.notify_one();
    }
    T pop() {
        std::unique_lock lk { mx };
        notEmpty.wait(lk,
          [this] {return !q.empty();});
        T t = q.front();
        q.pop();
        return t;
    }

    bool empty() const {
        std::scoped_lock const lk { mx };
        return q.empty();
    }
    void swap(ThreadsafeQueue & other) {
        if (this == &other) {
            return;
        }
        std::scoped_lock const both { mx, other.mx };
        // no need to swap cv or mx
        std::swap(q, other.q);
    }
    friend void swap(ThreadsafeQueue & left,
                     ThreadsafeQueue & other){
        left.swap(other);
    }
private:
    mutable MUTEX mx { };
    std::condition_variable notEmpty { };
    std::queue<T> q { };
};
}

#endif /* THREADSAFEEXCHANGE_H_ */
