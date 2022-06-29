#ifndef PETERSONMUTEXVOLATILE_H_
#define PETERSONMUTEXVOLATILE_H_


struct PetersonMutexVolatile {
    // acquire lock by thread 0
    void thread0Lock() {
        state0 = true;
        turn = 1;
        while (turn == 1 && state1);
    }

    void thread0Unlock() {
        state0 = false;
    }

    // acquire lock by thread 1
    void thread1Lock() {
        state1 = true;
        turn = 0;
        while (turn == 0 && state0);
    }

    // release lock by thread 1
    void thread1Unlock() {
        state1 = false;
    }
private:
    volatile bool state0 { false };
    volatile bool state1 { false };
    volatile int turn { 0 };
};


#endif /* PETERSONMUTEXVOLATILE_H_ */
