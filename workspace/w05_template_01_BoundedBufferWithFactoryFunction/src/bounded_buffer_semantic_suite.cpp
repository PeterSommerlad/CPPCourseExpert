#include "bounded_buffer_semantic_suite.h"
#include "BoundedBuffer.h"
#include "cute.h"
#include "MemoryOperationCounter.h"
#include <utility>



void test_buffer_push_copies_element() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer { };
	MemoryOperationCounter counter { }, expected { 0, 1, true };
	buffer.push(counter);
	ASSERT_EQUAL(expected, buffer.front());
}

void test_buffer_push_moves_element() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer { };
	MemoryOperationCounter counter { }, expected { 1, 0, true };
	buffer.push(std::move(counter));
	ASSERT_EQUAL(expected, buffer.front());
}

void test_element_in_buffer_is_copied_along_copy_constructor() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{};
	MemoryOperationCounter counter{}, expected{0, 2, true};
	buffer.push(counter);
	BoundedBuffer<MemoryOperationCounter, 1> const & constBuffer = buffer;
	BoundedBuffer<MemoryOperationCounter, 1> bufferCopied{constBuffer};
	ASSERT_EQUAL(expected, bufferCopied.front());
}

void test_element_in_buffer_is_copied_along_assignment_operator() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{}, bufferCopied{};
	MemoryOperationCounter counter{}, expected{0, 2, true};
	buffer.push(counter);
	BoundedBuffer<MemoryOperationCounter, 1> const & constBuffer = buffer;
	bufferCopied = constBuffer;
	ASSERT_EQUAL(expected, bufferCopied.front());
}

void test_element_in_buffer_is_moved_along_move_constructor() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{};
	MemoryOperationCounter counter{}, expected{2, 0, true};
	buffer.push(std::move(counter));
	BoundedBuffer<MemoryOperationCounter, 1> bufferCopied{std::move(buffer)};
	ASSERT_EQUAL(expected, bufferCopied.front());
}

void test_element_in_buffer_is_moved_along_assignment_operator() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{}, bufferMoved{};
	MemoryOperationCounter counter{}, expected{2, 0, true};
	buffer.push(std::move(counter));
	bufferMoved = std::move(buffer);
	ASSERT_EQUAL(expected, bufferMoved.front());
}


void test_element_in_buffer_is_copied_along_assignment_operator_multiple_copies() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{}, intermediate1{}, intermediate2{}, bufferCopied{};
	MemoryOperationCounter counter{}, expected{0, 4, true};
	buffer.push(counter);
	bufferCopied = intermediate2 = intermediate1 = buffer;
	ASSERT_EQUAL(expected, bufferCopied.front());
}


void test_element_in_buffer_is_moved_along_assignment_operator_multiple_moves() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{}, intermediate1{}, intermediate2{}, bufferMoved{};
	MemoryOperationCounter counter{}, expected{4, 0, true};
	buffer.push(std::move(counter));
	bufferMoved = std::move(intermediate1 = std::move(intermediate2 = std::move(buffer)));
	ASSERT_EQUAL(expected, bufferMoved.front());
}


void test_element_buffer_copy_is_returned_from_assignment() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{}, bufferCopied{};
	MemoryOperationCounter counter{}, expected{0, 2, true};
	buffer.push(counter);
	BoundedBuffer<MemoryOperationCounter, 1> const & constBuffer = buffer;
	ASSERT_EQUAL(expected, (bufferCopied = constBuffer).front());
}


void test_element_buffer_moved_is_returned_from_assignment() {
	BoundedBuffer<MemoryOperationCounter, 1> buffer{}, bufferMoved{};
	MemoryOperationCounter counter{}, expected{2, 0, true};
	buffer.push(std::move(counter));
	ASSERT_EQUAL(expected, (bufferMoved = std::move(buffer)).front());
}

cute::suite make_suite_bounded_buffer_semantic_suite() {
	cute::suite s;
	s.push_back(CUTE(test_buffer_push_moves_element));
	s.push_back(CUTE(test_buffer_push_copies_element));
	s.push_back(CUTE(test_element_in_buffer_is_copied_along_copy_constructor));
	s.push_back(CUTE(test_element_in_buffer_is_copied_along_assignment_operator));
	s.push_back(CUTE(test_element_in_buffer_is_moved_along_move_constructor));
	s.push_back(CUTE(test_element_in_buffer_is_moved_along_assignment_operator));
	s.push_back(CUTE(test_element_in_buffer_is_copied_along_assignment_operator_multiple_copies));
	s.push_back(CUTE(test_element_in_buffer_is_moved_along_assignment_operator_multiple_moves));
	s.push_back(CUTE(test_element_buffer_copy_is_returned_from_assignment));
	s.push_back(CUTE(test_element_buffer_moved_is_returned_from_assignment));
	return s;
}

