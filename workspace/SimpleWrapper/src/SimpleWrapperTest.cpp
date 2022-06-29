#include "wrapper.h"
#include "wrapper_value.h"
#include "wrapper_nonmovable.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <memory>
#include <sstream>
#include <utility>


struct nonmovable{
  explicit nonmovable(int x):val{x}{}
    nonmovable& operator=(nonmovable&&)=delete; // rule of desdemova
  int val;
};

namespace with_ref{
using wrapit::wrapper;

void testWithSimpleRegularType() {
    wrapper<int> wi{42};
    ASSERT_EQUAL(42,wi.value);
}

void testMoveOnlyType(){
    auto x = std::make_unique<int>(42);
    // wrapper<std::unique_ptr<int>> w{x}; // doesn't compile
    wrapper<std::unique_ptr<int>> w{std::move(x)};

    ASSERT_EQUAL(42,*w.value);
}
void testReplacement(){
  wrapper wup{std::make_unique<int>(42)};
  wup.replace(std::unique_ptr<int>{});
  wup.replace(nullptr);
  ASSERT_EQUAL(nullptr,wup.value);
}
void testReplacementwithlvalue(){
  wrapper wup{std::make_unique<int>(42)};
  std::unique_ptr<int> null{};
  //wup.replace(null);  // doesn't compile
  wup.replace(std::move(null));
  ASSERT_EQUAL(nullptr,wup.value);
}

void testnonmovable(){
  //wrapper<nonmovable> w{nonmovable{42}};
  //wrapper<nonmovable> w{42};
}

}

namespace with_value{
using wrap_value::wrapper;


void testWithSimpleRegularType() {
    wrapper<int> wi{42};
    ASSERT_EQUAL(42,wi.value);
}

void testMoveOnlyType(){
    auto x = std::make_unique<int>(42);
    using wrapit::wrapper;
    // wrapper<std::unique_ptr<int>> w{x}; // doesn't compile
    wrapper<std::unique_ptr<int>> w{std::move(x)};

    ASSERT_EQUAL(42,*w.value);
}
void testnonmovable(){
  //wrapper<nonmovable> w{nonmovable{42}};
  //wrapper<nonmovable> w{42};
}

void testReplacement(){
  wrapper wup{std::make_unique<int>(42)};
  wup.replace(std::unique_ptr<int>{});
  wup.replace(nullptr);
  ASSERT_EQUAL(nullptr,wup.value);
}
void testReplacementwithlvalue(){
  wrapper wup{std::make_unique<int>(42)};
  std::unique_ptr<int> null{};
  //wup.replace(null);  // doesn't compile
  wup.replace(std::move(null)); // internally uses move assignment
  ASSERT_EQUAL(nullptr,wup.value);
}

}
namespace with_forwarding{
using wrap_nonmovable::wrapper;
using wrap_nonmovable::wrapit;

void testWithSimpleRegularType() {
    wrapper<int> wi{42};
    ASSERT_EQUAL(42,wi.value);
}

void testMoveOnlyType(){
    auto x = std::make_unique<int>(42);
    using wrapit::wrapper;
    // wrapper<std::unique_ptr<int>> w{x}; // doesn't compile
    wrapper<std::unique_ptr<int>> w{std::move(x)};

    ASSERT_EQUAL(42,*w.value);
}
void testnonmovable(){
    wrapper<nonmovable> w{42};
    ASSERT_EQUAL(42,w.value.val);
}

void testReplacement(){
  wrapper<std::unique_ptr<int>> wup{std::make_unique<int>(42)};
  wup.replace(std::unique_ptr<int>{});
  wup.replace(nullptr);
  ASSERT_EQUAL(nullptr,wup.value);
}
void testReplacementwithlvalue(){
  wrapper<std::unique_ptr<int>> wup{std::make_unique<int>(42)};
  std::unique_ptr<int> null{};
  //wup.replace(null);  // doesn't compile
  wup.replace(std::move(null));
  ASSERT_EQUAL(nullptr,wup.value);
}
void testWrapItFunction(){
  std::ostringstream out{};
  wrapit([](auto &os){ os << "was wrapped";},out);
  ASSERT_EQUAL("was wrapped",out.str());
}
void testWrapItFunctionWithCapture(){
  std::ostringstream out{};
  wrapit([&out](auto x){ out << x << " was wrapped";},42);
  ASSERT_EQUAL("42 was wrapped",out.str());
}
void testWrapItFunctionWithnon_copyable(){
  std::ostringstream out{};
  wrapit([&out](auto x){ out << *x << " was wrapped";},std::make_unique<int>(42));
  ASSERT_EQUAL("42 was wrapped",out.str());
}
struct nmv_def {
  nmv_def operator=(nmv_def&&)=delete;
  int get() { return 42; }
};
void testNonMovableWithDefaultCtor(){
  wrapper<nmv_def> w{};
  ASSERT_EQUAL(42,w.value.get());
}
struct nmv_2ref {
  nmv_2ref(int &i, std::unique_ptr<int> p)
  : i{i}, up{std::move(p)}{}
  nmv_2ref operator=(nmv_2ref&&)=delete;
  int &i;
  std::unique_ptr<int> up;
};
void testNonMovableWith2Arguments(){
  int i{42};
  wrapper<nmv_2ref> w{i,std::make_unique<int>(43)};
  ASSERT_EQUAL(42*43,w.value.i * *w.value.up);
}
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(with_value::testWithSimpleRegularType));
	s.push_back(CUTE(with_value::testMoveOnlyType));
	s.push_back(CUTE(with_ref::testWithSimpleRegularType));
	s.push_back(CUTE(with_ref::testMoveOnlyType));
	s.push_back(CUTE(with_ref::testReplacement));
	s.push_back(CUTE(with_value::testReplacement));
	s.push_back(CUTE(with_ref::testReplacementwithlvalue));
	s.push_back(CUTE(with_value::testReplacementwithlvalue));
	s.push_back(CUTE(with_forwarding::testWithSimpleRegularType));
	s.push_back(CUTE(with_forwarding::testMoveOnlyType));
	s.push_back(CUTE(with_forwarding::testnonmovable));
	s.push_back(CUTE(with_forwarding::testReplacement));
	s.push_back(CUTE(with_forwarding::testReplacementwithlvalue));
	s.push_back(CUTE(with_forwarding::testWrapItFunction));
	s.push_back(CUTE(with_forwarding::testWrapItFunctionWithCapture));
	s.push_back(CUTE(with_forwarding::testWrapItFunctionWithnon_copyable));
	s.push_back(CUTE(with_forwarding::testNonMovableWithDefaultCtor));
	s.push_back(CUTE(with_forwarding::testNonMovableWith2Arguments));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
