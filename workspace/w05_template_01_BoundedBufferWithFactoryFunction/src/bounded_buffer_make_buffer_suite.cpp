#include "bounded_buffer_make_buffer_suite.h"
#include "BoundedBuffer.h"
#include "MemoryOperationCounter.h"
#include "cute.h"

//--- a) ---

void test_make_bounded_buffer_from_rvalue_argument_contains_one_element() {
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{});
  ASSERT_EQUAL(1, buffer.size());
}

void test_make_bounded_buffer_from_rvalue_argument_object_moved() {
  MemoryOperationCounter expected{1, 0, true};
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{});
  ASSERT_EQUAL(expected, buffer.front());
}

void test_bounded_buffer_constructed_with_lvalue_argument_object_copied() {
  MemoryOperationCounter expected{0, 1, true};
  MemoryOperationCounter insertee{};
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(insertee);
  ASSERT_EQUAL(expected, buffer.front());
}

void test_bounded_buffer_constructed_with_const_lvalue_argument_object_copied() {
  MemoryOperationCounter expected{0, 1, true};
  MemoryOperationCounter const insertee{};
  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(insertee);
  ASSERT_EQUAL(expected, buffer.front());
}


//--- b) ---


void test_make_bounded_buffer_from_two_rvalue_arguments_contains_two_elements() {
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, MemoryOperationCounter{});
//  ASSERT_EQUAL(2, buffer.size());
}

void test_make_bounded_buffer_from_two_lvalue_arguments_contains_two_elements() {
//  MemoryOperationCounter element1{}, element2{};
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(element1, element2);
//  ASSERT_EQUAL(2, buffer.size());
}

void test_make_bounded_buffer_from_too_many_elements_throws() {
//  ASSERT_THROWS((BoundedBuffer<int, 1>::make_buffer(1, 2)), std::invalid_argument);
}

void test_make_bounded_buffer_from_two_rvalue_arguments_first_element_moved() {
//  MemoryOperationCounter expected{1, 0, true};
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, MemoryOperationCounter{});
//
//  ASSERT_EQUAL(expected, buffer.front());
}

void test_make_bounded_buffer_from_two_rvalue_arguments_second_element_moved() {
//  MemoryOperationCounter expected{1, 0, true};
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, MemoryOperationCounter{});
//  ASSERT_EQUAL(expected, buffer.back());
}

void test_make_bounded_buffer_from_two_rvalue_arguments_first_element_copied() {
//  MemoryOperationCounter expected{0, 1, true};
//  MemoryOperationCounter lvalue{};
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(lvalue, MemoryOperationCounter{});
//  ASSERT_EQUAL(expected, buffer.front());
}

void test_make_bounded_buffer_from_two_mixed_arguments_second_element_moved() {
//  MemoryOperationCounter expected{1, 0, true};
//  MemoryOperationCounter lvalue{};
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(lvalue, MemoryOperationCounter{});
//  ASSERT_EQUAL(expected, buffer.back());
}

void test_make_bounded_buffer_from_two_rvalue_arguments_second_element_copied() {
//  MemoryOperationCounter expected{0, 1, true};
//  MemoryOperationCounter lvalue{};
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, lvalue);
//  ASSERT_EQUAL(expected, buffer.back());
}

void test_make_bounded_buffer_from_two_mixed_arguments_first_element_moved() {
//  MemoryOperationCounter expected{1, 0, true};
//  MemoryOperationCounter lvalue{};
//  BoundedBuffer<MemoryOperationCounter, 15> buffer = BoundedBuffer<MemoryOperationCounter, 15>::make_buffer(MemoryOperationCounter{}, lvalue);
//  ASSERT_EQUAL(expected, buffer.front());
}


cute::suite make_suite_bounded_buffer_make_buffer_suite() {
	cute::suite s { };
	//--- a) ---
	s.push_back(CUTE(test_make_bounded_buffer_from_rvalue_argument_contains_one_element));
	s.push_back(CUTE(test_make_bounded_buffer_from_rvalue_argument_object_moved));
	s.push_back(CUTE(test_bounded_buffer_constructed_with_lvalue_argument_object_copied));
	s.push_back(CUTE(test_bounded_buffer_constructed_with_const_lvalue_argument_object_copied));

	//--- b) ---
	s.push_back(CUTE(test_make_bounded_buffer_from_two_rvalue_arguments_contains_two_elements));
	s.push_back(CUTE(test_make_bounded_buffer_from_two_lvalue_arguments_contains_two_elements));
	s.push_back(CUTE(test_make_bounded_buffer_from_too_many_elements_throws));
	s.push_back(CUTE(test_make_bounded_buffer_from_two_rvalue_arguments_first_element_moved));
	s.push_back(CUTE(test_make_bounded_buffer_from_two_rvalue_arguments_second_element_moved));
	s.push_back(CUTE(test_make_bounded_buffer_from_two_rvalue_arguments_first_element_copied));
	s.push_back(CUTE(test_make_bounded_buffer_from_two_mixed_arguments_second_element_moved));
	s.push_back(CUTE(test_make_bounded_buffer_from_two_rvalue_arguments_second_element_copied));
	s.push_back(CUTE(test_make_bounded_buffer_from_two_mixed_arguments_first_element_moved));
	return s;
}
