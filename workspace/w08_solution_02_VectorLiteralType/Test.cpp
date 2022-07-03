#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "Vector.h"

#include <sstream>


void testCreateVectorWithSingleElement() {
	constexpr Vector<double, 1> v{1.0};
	static_assert(v[0] == 1.0);
	ASSERT_EQUAL(1.0, v[0]);
}

void testCreateVectorWithTwoElements() {
	constexpr Vector<double, 2> v{1.0, 2.0};
	static_assert(v[0] == 1.0);
	static_assert(v[1] == 2.0);
	ASSERT_EQUAL(1.0, v[0]);
	ASSERT_EQUAL(2.0, v[1]);
}

void testCreateVectorWithoutElements() {
	constexpr Vector<double, 0> v{};
	ASSERT(true);
}

void testAccessOutOfBoundsThrows() {
	constexpr Vector<double, 1> v{1.0};
	//static_assert(v[1] == 0.0); // out of range!
	ASSERT_THROWS(v[1], std::out_of_range);
}

void testDeduceTemplateArguments() {
	constexpr Vector v{1.0, 2.0};
	static_assert(v[0] == 1.0);
	static_assert(v[1] == 2.0);
	ASSERT_EQUAL(1.0, v[0]);
	ASSERT_EQUAL(2.0, v[1]);
}

constexpr auto create() {
	Vector v{1.0, 2.0};
	v[0] = 3.0;
	return v;
}

void testAllowModificationOfNonConstElement() {
	constexpr auto v = create();
	static_assert(v[0] == 3.0);
	static_assert(v[1] == 2.0);
	ASSERT_EQUAL(3.0, v[0]);
	ASSERT_EQUAL(2.0, v[1]);
}

void testCalculateLengthOfZeroVector() {
	constexpr Vector v{0.0, 0.0, 0.0, 0.0};
	constexpr auto length = v.length();
	static_assert(length == 0.0);
	ASSERT_EQUAL(0.0, length);
}

void testCalculateLength() {
	constexpr Vector v{1.0, 2.0, 3.0};
	constexpr auto length = v.length();
	static_assert(length == std::sqrt(14.0));
	ASSERT_EQUAL(std::sqrt(14.0), length);
}

void testCalculateLengthOfUnitVector() {
	constexpr Vector v{1.0 / std::sqrt(14.0), 2.0 / std::sqrt(14.0), 3.0 / std::sqrt(14.0)};
	constexpr auto length = v.length();
	static_assert(length == 1.0);
	ASSERT_EQUAL(1.0, length);
}

void testEqualityComparison() {
	constexpr Vector v{1.0, 2.5, 3.2};
	static_assert(v == v);
	ASSERT_EQUAL(v, v);
}

void testUnequalityComparision() {
	constexpr Vector lhs{1.0, 2.5, 3.3};
	constexpr Vector rhs{1.0, 2.5, 3.1};
	static_assert(lhs != rhs);
	ASSERT_NOT_EQUAL_TO(lhs, rhs);
}

void testOutputOperator() {
	constexpr Vector v{1.1, 2.5, 3.3};
	std::ostringstream out { };
	out << v;
	ASSERT_EQUAL("(1.1, 2.5, 3.3)", out.str());
}

void testInnerProduct() {
	constexpr Vector lhs{1.0, 2.0, 3.0, 4.0};
	constexpr Vector rhs{4.2, 1.1, 0.0, 9.5};
	constexpr double expected = 44.4;
	static_assert(lhs.innerProduct(rhs) == expected);
	ASSERT_EQUAL(expected, lhs.innerProduct(rhs));
}

void testDifferentTypes() {
	//constexpr Vector fail{1., 1.f};
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testCreateVectorWithSingleElement));
	s.push_back(CUTE(testCreateVectorWithTwoElements));
	s.push_back(CUTE(testCreateVectorWithoutElements));
	s.push_back(CUTE(testAccessOutOfBoundsThrows));
	s.push_back(CUTE(testDeduceTemplateArguments));
	s.push_back(CUTE(testAllowModificationOfNonConstElement));
	s.push_back(CUTE(testCalculateLengthOfZeroVector));
	s.push_back(CUTE(testCalculateLength));
	s.push_back(CUTE(testCalculateLengthOfUnitVector));
	s.push_back(CUTE(testEqualityComparison));
	s.push_back(CUTE(testUnequalityComparision));
	s.push_back(CUTE(testOutputOperator));
	s.push_back(CUTE(testInnerProduct));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
