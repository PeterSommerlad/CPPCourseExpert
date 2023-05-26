#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <iterator>
#include <limits>
#include <stdexcept>
#include <vector>
// pass by value gives overload conflict
int increment(int const &value){
  return value+1;
}
int increment(int &value){
  if (value == std::numeric_limits<int>::max())
    throw std::overflow_error{"integer increment overflow"};
  return ++value;
}
void exercise01_1() {
  int const value = 19;
  auto const next = increment(value);
  ASSERT_EQUAL(20, next);
}
void exercise01_2(){
  int value = 19;
  increment(value);
  ASSERT_EQUAL(20, value);
}

void exercise01_3(){
  int maxValue = std::numeric_limits<int>::max();
  ASSERT_THROWS(increment(maxValue), std::overflow_error);
}

namespace templ_04 {


template<typename T>
auto increment(T &value, T const limit = std::numeric_limits<T>::max()){
  if constexpr (!std::is_unsigned_v<T>){
    if (value >= limit) // should not >= with iterators...
      throw std::overflow_error{"increment overflow"};
  }
  return ++value;

}

void exercise01_4(){
  double value = 1.5;
  increment(value);
  ASSERT_EQUAL(2.5, value);
}

void exercise01_5(){
  auto maxValue = std::numeric_limits<unsigned long long>::max();
  increment(maxValue);
  ASSERT_EQUAL(0, maxValue);
}
void exercise01_81(){
  std::vector<int> v{1};
  auto it = std::end(v);
  ASSERT_THROWS(increment(it, std::end(v)), std::overflow_error);
}
void exercise01_82(){
  double d{9.5};
  ASSERT_THROWS(increment(d, 9.0), std::overflow_error);
}
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(exercise01_1));
	s.push_back(CUTE(exercise01_2));
	s.push_back(CUTE(exercise01_3));
	s.push_back(CUTE(templ_04::exercise01_4));
	s.push_back(CUTE(templ_04::exercise01_5));
	s.push_back(CUTE(templ_04::exercise01_81));
	s.push_back(CUTE(templ_04::exercise01_82));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
