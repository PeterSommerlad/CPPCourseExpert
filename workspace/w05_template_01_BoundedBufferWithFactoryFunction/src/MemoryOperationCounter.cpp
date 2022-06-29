#include "MemoryOperationCounter.h"

#include <ostream>
#include <utility>

MemoryOperationCounter::MemoryOperationCounter(unsigned moves, unsigned copies, bool known_state) :
		moves { moves }, copies { copies }, known_state { known_state } {
}

MemoryOperationCounter::MemoryOperationCounter(MemoryOperationCounter&& source) :
		moves { std::move(source.moves) }, copies { std::move(source.copies) }, known_state { std::move(source.known_state) } {
	moves++;
	source.known_state = false;
}

MemoryOperationCounter::MemoryOperationCounter(MemoryOperationCounter const & source) :
		moves { std::move(source.moves) }, copies { std::move(source.copies) }, known_state { std::move(source.known_state) } {
	copies++;
}

MemoryOperationCounter& MemoryOperationCounter::operator =(MemoryOperationCounter&& source) & noexcept
{
	copyFrom(source);
	moves++;
	source.known_state = false;
	return *this;
}

MemoryOperationCounter& MemoryOperationCounter::operator =(MemoryOperationCounter const & source) & noexcept
{
	copyFrom(source);
	copies++;
	return *this;
}

bool MemoryOperationCounter::operator ==(MemoryOperationCounter const & other) const {
	return (moves == other.moves) && (copies == other.copies) == (known_state == other.known_state);
}

void MemoryOperationCounter::print(std::ostream& os) const {
	os << "MemoryOperationsCounter{moves: " << moves << ", copies: " << copies << ", known_state: " << known_state << "}\n";
}

void MemoryOperationCounter::copyFrom(MemoryOperationCounter const & source) {
	moves = source.moves;
	copies = source.copies;
	known_state = source.known_state;
}

std::ostream& operator <<(std::ostream& os, MemoryOperationCounter const & counter) {
	counter.print(os);
	return os;
}
