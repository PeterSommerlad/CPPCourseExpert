#include "NotOnHeap.hpp"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <new>
#include <cstddef>
#include <vector>
#include <memory>


//Allocation as local variable
void test_stack_allocation_works() {
	not_on_heap const x{};
	ASSERTM("start writing tests", x.valid());
}

//Allocation as static variable
void test_static_allocation_works() {
	static not_on_heap const y{};
	ASSERTM("start writing tests", y.valid());
}

//Allocation on heap with new
void test_heap_allocation_throws() {
	ASSERT_THROWS(new not_on_heap{}, std::bad_alloc);
}

//Allocation in array on heap
void test_heap_alloction_of_array_throws() {
	ASSERT_THROWS(new not_on_heap[2]{}, std::bad_alloc);
}

//Allocation in vector on heap
void test_vector_still_works() {
	std::vector<not_on_heap> const v{3};
	ASSERT_EQUAL(3, v.size());
}

//Allocation with make_unique
void test_with_make_unique() {
	ASSERT_THROWS(std::make_unique<not_on_heap>(), std::bad_alloc);
}

//Allocation as unique_ptr with new
void test_create_unique_ptr_from_new() {
	ASSERT_THROWS(std::unique_ptr<not_on_heap>{new not_on_heap{}}, std::bad_alloc);
}

//Allocation with make_shared
void test_with_make_shared() {
	auto sp = std::make_shared<not_on_heap>();
	ASSERTM("should be real pointer", sp != nullptr);
	//ASSERT_THROWS(std::make_shared<not_on_heap>(), std::bad_alloc);
}

//Allocation with placement new
void test_with_placement_new() {
	std::byte * const spaceForNotOnHeap = new std::byte[sizeof(not_on_heap)] { };
	not_on_heap const * const ptr = ::new (spaceForNotOnHeap) not_on_heap { };
	ASSERT(ptr->valid());
	delete ptr;
}

void runAllTests(int argc, char const *argv[]) {
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(test_stack_allocation_works));
	s.push_back(CUTE(test_heap_allocation_throws));
	s.push_back(CUTE(test_heap_alloction_of_array_throws));
	s.push_back(CUTE(test_vector_still_works));
	s.push_back(CUTE(test_with_make_unique));
	s.push_back(CUTE(test_with_make_shared));
	s.push_back(CUTE(test_create_unique_ptr_from_new));
	s.push_back(CUTE(test_static_allocation_works));
	s.push_back(CUTE(test_with_placement_new));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}

