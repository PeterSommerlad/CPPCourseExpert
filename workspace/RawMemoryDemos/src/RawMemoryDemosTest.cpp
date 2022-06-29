#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <array>

#include <cstddef>

#include <memory>

struct demo {
  int i; // might have a hole here
  double d;
};
static_assert(sizeof(demo)> sizeof(int)+sizeof(double),"oops no padding");
void demo_raw_byte_array_heap(){
  auto buf = std::make_unique<std::byte[]>(sizeof(demo));
  auto ptr = new(buf.get()) demo {42,3.14};
  ASSERT_EQUAL(42*3.14 , ptr->i * ptr->d);
  // struct is not destroyed, memory released
}
void demo_raw_byte_array_stack(){
  alignas(demo) std::array<std::byte, sizeof(demo)>  buf;
  auto ptr = new(buf.data()) demo {42,3.14};
  ASSERT_EQUAL(42*3.14 , ptr->i * ptr->d);
}


void demo_raw_byte_array_for_overwrite_heap(){
  auto buf = std::make_unique_for_overwrite<std::byte[]>(sizeof(demo));
  auto ptr = new(buf.get()) demo {42,3.14};
  ASSERT_EQUAL(42*3.14 , ptr->i * ptr->d);
  // struct is not destroyed, memory released
}

void demo_object_for_overwrite_heap(){
  auto ptr = std::make_unique_for_overwrite<demo>();
  *ptr=demo {42,3.14};
  ASSERT_EQUAL(42*3.14 , ptr->i * ptr->d);
  // struct is not destroyed, memory released
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(demo_raw_byte_array_heap));
	s.push_back(CUTE(demo_raw_byte_array_stack));
	s.push_back(CUTE(demo_raw_byte_array_for_overwrite_heap));
	s.push_back(CUTE(demo_object_for_overwrite_heap));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
