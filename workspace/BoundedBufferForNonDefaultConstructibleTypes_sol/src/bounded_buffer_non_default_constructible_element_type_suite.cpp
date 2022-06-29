#include "bounded_buffer_non_default_constructible_element_type_suite.h"
#include "cute.h"
#include "BoundedBuffer.h"
#include <stdexcept>
#include <string>
#include <utility>
using heap_non_default::BoundedBuffer;

struct NonDefaultConstructible {
	explicit NonDefaultConstructible(int) : value{1234} {}

	~NonDefaultConstructible() {
		throwIfNotInitialized();
		nOfDtorCalls++;
	}

	NonDefaultConstructible(NonDefaultConstructible const & other) : value{other.value} {
		throwIfNotInitialized();
		nOfCopyConstructions++;
	}

	NonDefaultConstructible& operator=(NonDefaultConstructible const & other) {
		throwIfNotInitialized();
		other.throwIfNotInitialized();
		value = other.value;
		nOfCopyAssignments++;
		return *this;
	}

	NonDefaultConstructible& operator=(NonDefaultConstructible && other) {
		throwIfNotInitialized();
		other.throwIfNotInitialized();
		std::swap(value, other.value);
		nOfMoveAssignments++;
		return *this;
	}

	NonDefaultConstructible(NonDefaultConstructible && other) : value{1234} {
		other.throwIfNotInitialized();
		std::swap(value, other.value);
		nOfMoveConstructions++;
	}

	static inline unsigned nOfCopyConstructions{0};
	static inline unsigned nOfCopyAssignments{0};
	static inline unsigned nOfMoveConstructions{0};
	static inline unsigned nOfMoveAssignments{0};
	static inline unsigned nOfDtorCalls{0};
private:
	void throwIfNotInitialized() const {
		if (value != 1234) {
			throw std::logic_error{"Operation on NDC with value: " + std::to_string(value)};
		}
	}
	volatile unsigned value;
};

void resetCounters() {
	NonDefaultConstructible::nOfCopyConstructions = 0;
	NonDefaultConstructible::nOfCopyAssignments = 0;
	NonDefaultConstructible::nOfMoveConstructions = 0;
	NonDefaultConstructible::nOfMoveAssignments = 0;
	NonDefaultConstructible::nOfDtorCalls = 0;
}

void test_new_buffer_of_nondefaultconstructible_invokes_no_destructors() {
	resetCounters();
	BoundedBuffer<NonDefaultConstructible> buffer{5};
	ASSERT_EQUAL(0, NonDefaultConstructible::nOfDtorCalls);
}

void test_element_in_buffer_is_destroyed_once() {
	{
		BoundedBuffer<NonDefaultConstructible> buffer{5};
		buffer.push(NonDefaultConstructible{23});
		resetCounters();
	}
	ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

void test_element_in_moved_buffer_is_destroyed_once() {
	{
		BoundedBuffer<NonDefaultConstructible> buffer{5};
		buffer.push(NonDefaultConstructible{23});
		resetCounters();

		BoundedBuffer<NonDefaultConstructible> moved{std::move(buffer)};
	}

	ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

void test_every_element_in_copied_buffer_is_destroyed_once() {
	{
		BoundedBuffer<NonDefaultConstructible> buffer{5};
		buffer.push(NonDefaultConstructible{23});
		resetCounters();

		BoundedBuffer<NonDefaultConstructible> copy{buffer};
	}
	ASSERT_EQUAL(2, NonDefaultConstructible::nOfDtorCalls);
}

void test_pop_destroys_element() {
	BoundedBuffer<NonDefaultConstructible> buffer{5};
	buffer.push(NonDefaultConstructible{23});
	resetCounters();

	buffer.pop();

	ASSERT_EQUAL(1, NonDefaultConstructible::nOfDtorCalls);
}

void test_lvalue_push_copies_element() {
	resetCounters();
	BoundedBuffer<NonDefaultConstructible> buffer{5};
	NonDefaultConstructible element{23};

	buffer.push(element);

	ASSERT_EQUAL(1, NonDefaultConstructible::nOfCopyConstructions);
}

void test_rvalue_push_moves_element() {
	resetCounters();
	BoundedBuffer<NonDefaultConstructible> buffer{5};
	NonDefaultConstructible element{23};

	buffer.push(std::move(element));

	ASSERT_EQUAL(1, NonDefaultConstructible::nOfMoveConstructions);
}

void test_lvalue_push_must_not_copy_assign() {
	BoundedBuffer<NonDefaultConstructible> buffer{5};
	NonDefaultConstructible element{23};

	resetCounters();
	buffer.push(element);

	ASSERT_EQUAL(0, NonDefaultConstructible::nOfCopyAssignments);
}

void test_rvalue_push_must_not_move_assign() {
	BoundedBuffer<NonDefaultConstructible> buffer{5};
	NonDefaultConstructible element{23};

	resetCounters();
	buffer.push(std::move(element));

	ASSERT_EQUAL(0, NonDefaultConstructible::nOfMoveAssignments);
}

struct NonCopyableNonMovable {
    NonCopyableNonMovable(int i , double d):i{i},d{d} {}
    // Rule of DesDeMovA:
    NonCopyableNonMovable& operator=(NonCopyableNonMovable&&)noexcept = delete;
    int i;
    double d;
};

void test_emplace_works(){
	BoundedBuffer<NonCopyableNonMovable> buffer{5};
	buffer.push_emplace(42,3.14);
	ASSERT_EQUAL(42,buffer.front().i);
}



cute::suite make_suite_bounded_buffer_non_default_constructible_element_type_suite(){
	cute::suite s;
	s.push_back(CUTE(test_new_buffer_of_nondefaultconstructible_invokes_no_destructors));
	s.push_back(CUTE(test_element_in_buffer_is_destroyed_once));
	s.push_back(CUTE(test_element_in_moved_buffer_is_destroyed_once));
	s.push_back(CUTE(test_every_element_in_copied_buffer_is_destroyed_once));
	s.push_back(CUTE(test_pop_destroys_element));
	s.push_back(CUTE(test_lvalue_push_copies_element));
	s.push_back(CUTE(test_rvalue_push_moves_element));
	s.push_back(CUTE(test_lvalue_push_must_not_copy_assign));
	s.push_back(CUTE(test_rvalue_push_must_not_move_assign));
	s.push_back(CUTE(test_emplace_works));
	return s;
}



