#include "bounded_queue_signatures_suite.h"

#include "cute.h"
#include "BoundedQueue.h"
#include <chrono>



void test_bounded_queue_size_type_is_size_t() {
    ASSERT((std::is_same_v<size_t,BoundedQueue<int>::size_type> ));
}

void test_const_bounded_queue_type_of_empty_is_bool() {
	BoundedQueue<int> const queue { 15 };
    ASSERT((std::is_same_v<bool,decltype(queue.empty())> ));
}

void test_const_bounded_queue_type_of_full_is_bool() {
	BoundedQueue<int> const queue { 15 };
    ASSERT((std::is_same_v<bool,decltype(queue.full())> ));
}

void test_const_bounded_queue_type_of_size_is_size_t() {
	BoundedQueue<int> const queue { 15 };
    ASSERT((std::is_same_v<size_t,decltype(queue.size())> ));
}

void test_bounded_queue_type_of_push_of_const_lvalue_is_void() {
	BoundedQueue<int> queue { 15 };
	int const lvalue { 23 };
    ASSERT((std::is_same_v<void,decltype(queue.push(lvalue))> ));
}

void test_bounded_queue_type_of_push_of_rvalue_is_void() {
	BoundedQueue<int> queue { 15 };
    ASSERT((std::is_same_v<void,decltype(queue.push(23))> ));
}

void test_bounded_queue_type_of_try_push_of_const_lvalue_is_bool() {
	BoundedQueue<int> queue { 15 };
	int const lvalue { 23 };
    ASSERT((std::is_same_v<bool,decltype(queue.try_push(lvalue))> ));
}

void test_bounded_queue_type_of_try_push_of_rvalue_is_bool() {
	BoundedQueue<int> queue { 15 };
    ASSERT((std::is_same_v<bool,decltype(queue.try_push(23))> ));
}

void test_bounded_queue_type_of_pop_is_value_type() {
	BoundedQueue<int> queue { 15 };
    ASSERT((std::is_same_v<int,decltype(queue.pop())> ));
}

void test_bounded_queue_type_of_try_pop_is_bool() {
	BoundedQueue<int> queue { 15 };
	int popped_value { };
    ASSERT((std::is_same_v<bool,decltype(queue.try_pop(popped_value))> ));
}

void test_bounded_queue_type_of_swap_is_void() {
	BoundedQueue<int> queue { 15 }, other_queue { 15 };
    ASSERT((std::is_same_v<void,decltype(queue.swap(other_queue))> ));
}

void test_bounded_queue_type_of_try_push_for_is_bool() {
	BoundedQueue<int> queue { 15 };
    ASSERT((std::is_same_v<bool,decltype(queue.try_push_for(1, std::chrono::seconds{1}))> ));
}

void test_bounded_queue_type_of_try_pop_for_is_bool() {
	BoundedQueue<int> queue { 15 };
	int result{};
    ASSERT((std::is_same_v<bool,decltype(queue.try_pop_for(result, std::chrono::seconds{1}))> ));
}

cute::suite make_suite_bounded_queue_signatures_suite() {
	cute::suite s;
	s.push_back(CUTE(test_bounded_queue_size_type_is_size_t));
	s.push_back(CUTE(test_const_bounded_queue_type_of_empty_is_bool));
	s.push_back(CUTE(test_const_bounded_queue_type_of_full_is_bool));
	s.push_back(CUTE(test_const_bounded_queue_type_of_size_is_size_t));
	s.push_back(CUTE(test_bounded_queue_type_of_push_of_const_lvalue_is_void));
	s.push_back(CUTE(test_bounded_queue_type_of_push_of_rvalue_is_void));
	s.push_back(CUTE(test_bounded_queue_type_of_pop_is_value_type));
	s.push_back(CUTE(test_bounded_queue_type_of_swap_is_void));
	s.push_back(CUTE(test_bounded_queue_type_of_try_push_of_const_lvalue_is_bool));
	s.push_back(CUTE(test_bounded_queue_type_of_try_push_of_rvalue_is_bool));
	s.push_back(CUTE(test_bounded_queue_type_of_try_pop_is_bool));
	s.push_back(CUTE(test_bounded_queue_type_of_try_push_for_is_bool));
	s.push_back(CUTE(test_bounded_queue_type_of_try_pop_for_is_bool));
	return s;
}

