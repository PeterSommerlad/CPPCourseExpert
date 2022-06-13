#include "bounded_buffer_signatures_suite.h"
#include "cute.h"
#include "BoundedBuffer.h"
#include <array>

void test_bounded_buffer_value_type_is_value() {
	ASSERT((std::is_same_v<int, BoundedBuffer<int, 15>::value_type>));
}

void test_bounded_buffer_reference_type_is_reference() {
	ASSERT((std::is_same_v<int &,BoundedBuffer<int, 15>::reference> ));
}

void test_bounded_buffer_const_reference_type_is_const_reference() {
    ASSERT((std::is_same_v<int const &,BoundedBuffer<int, 15>::const_reference> ));
}

void test_bounded_buffer_container_type_is_array() {
    ASSERT((std::is_same_v<std::array<int, 15>,BoundedBuffer<int, 15>::container_type> ));
}

void test_bounded_buffer_size_type_is_size_t() {
    ASSERT((std::is_same_v<size_t,BoundedBuffer<int, 15>::size_type> ));
}

void test_const_bounded_buffer_type_of_empty_is_bool() {
	BoundedBuffer<int, 15> const buffer{};
    ASSERT((std::is_same_v<bool,decltype(buffer.empty())> ));
}

void test_const_bounded_buffer_type_of_full_is_bool() {
	BoundedBuffer<int, 15> const buffer{};
    ASSERT((std::is_same_v<bool,decltype(buffer.full())> ));
}

void test_bounded_buffer_front_type_is_reference_type() {
	BoundedBuffer<int, 15> buffer{};
    ASSERT((std::is_same_v<decltype(buffer)::reference,decltype(buffer.front())> ));
}

void test_const_bounded_buffer_front_type_is_const_reference_type() {
	BoundedBuffer<int, 15> const buffer{};
    ASSERT((std::is_same_v<decltype(buffer)::const_reference,decltype(buffer.front())> ));
}

void test_bounded_buffer_back_type_is_reference_type() {
	BoundedBuffer<int, 15> buffer{};
    ASSERT((std::is_same_v<decltype(buffer)::reference,decltype(buffer.back())> ));
}

void test_const_bounded_buffer_back_type_is_reference_type() {
	BoundedBuffer<int, 15> const buffer{};
    ASSERT((std::is_same_v<decltype(buffer)::const_reference,decltype(buffer.back())> ));
}

void test_const_bounded_buffer_type_of_size_is_size_type() {
	BoundedBuffer<int, 15> const buffer{};
    ASSERT((std::is_same_v<decltype(buffer)::size_type,decltype(buffer.size())> ));
}

void test_bounded_buffer_type_of_push_of_const_lvalue_is_void() {
	BoundedBuffer<int, 15> buffer{};
	int const lvalue{23};
    ASSERT((std::is_same_v<void,decltype(buffer.push(lvalue))> ));
}

void test_bounded_buffer_type_of_push_of_rvalue_is_void() {
	BoundedBuffer<int, 15> buffer{};
    ASSERT((std::is_same_v<void,decltype(buffer.push(23))> ));
}

void test_bounded_buffer_type_of_pop_is_void() {
	BoundedBuffer<int, 15> buffer{};
    ASSERT((std::is_same_v<void,decltype(buffer.pop())> ));
}



cute::suite make_suite_bounded_buffer_signatures_suite(){
	cute::suite s;
	s.push_back(CUTE(test_bounded_buffer_value_type_is_value));
	s.push_back(CUTE(test_bounded_buffer_reference_type_is_reference));
	s.push_back(CUTE(test_bounded_buffer_container_type_is_array));
	s.push_back(CUTE(test_bounded_buffer_const_reference_type_is_const_reference));
	s.push_back(CUTE(test_bounded_buffer_size_type_is_size_t));
	s.push_back(CUTE(test_const_bounded_buffer_type_of_empty_is_bool));
	s.push_back(CUTE(test_const_bounded_buffer_type_of_full_is_bool));
	s.push_back(CUTE(test_bounded_buffer_front_type_is_reference_type));
	s.push_back(CUTE(test_bounded_buffer_back_type_is_reference_type));
	s.push_back(CUTE(test_const_bounded_buffer_back_type_is_reference_type));
	s.push_back(CUTE(test_const_bounded_buffer_front_type_is_const_reference_type));
	s.push_back(CUTE(test_const_bounded_buffer_type_of_size_is_size_type));
	s.push_back(CUTE(test_bounded_buffer_type_of_push_of_const_lvalue_is_void));
	s.push_back(CUTE(test_bounded_buffer_type_of_push_of_rvalue_is_void));
	s.push_back(CUTE(test_bounded_buffer_type_of_pop_is_void));
	return s;
}



