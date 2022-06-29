#ifndef MEMORYOPERATIONCOUNTER_H_
#define MEMORYOPERATIONCOUNTER_H_

#include <iosfwd>



struct MemoryOperationCounter {
	MemoryOperationCounter() = default;
	MemoryOperationCounter(unsigned moves, unsigned copies, bool known_state);

	MemoryOperationCounter(MemoryOperationCounter&& source);

	MemoryOperationCounter& operator =(MemoryOperationCounter&& source) & noexcept;

	MemoryOperationCounter(MemoryOperationCounter const & source);

	MemoryOperationCounter& operator =(MemoryOperationCounter const & source) & noexcept;

	bool operator ==(MemoryOperationCounter const & other) const;

	void print(std::ostream& os) const;

private:
	unsigned moves { 0 };
	unsigned copies { 0 };
	bool known_state { true };

	void copyFrom(MemoryOperationCounter const & source);
};

std::ostream& operator <<(std::ostream& os, MemoryOperationCounter const & counter);

#endif /* MEMORYOPERATIONCOUNTER_H_ */
