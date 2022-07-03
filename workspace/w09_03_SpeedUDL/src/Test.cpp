#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "Speed.h"

using velocity::Speed;
using namespace velocity::tags;
using namespace velocity::literals;

template <typename Unit>
bool isFasterThanWalking(Speed<Unit> speed) {
	return velocity::speedCast<Kph>(speed) > 5.0_kph;
}

void overtakePedestrianAt10Kph() {
	ASSERT(isFasterThanWalking(10.0_kph));
}

void overtakePedestrianAt6dot2Mph(){
	ASSERT(isFasterThanWalking(6.2_mph));
}

void overtakePedestrianAt2dot8Mps(){
	ASSERT(isFasterThanWalking(2.8_mps));
}


void testConversionFromKphToMph() {
	ASSERT_EQUAL(1.60934_kph, 1.0_mph);
}

void testConversionFromMphToKph() {
	ASSERT_EQUAL(1.0_mph, 1.60934_kph);
}

void testConversionFromKphToMps() {
	ASSERT_EQUAL(3.6_kph, 1.0_mps);
}

void testConversionFromMpsToKph() {
	ASSERT_EQUAL(1.0_mps, 3.6_kph);
}

void testConversionFromMphToMps() {
	ASSERT_EQUAL(2.23694_mph, 1.0_mps);
}

void testConversionFromMpsToMph() {
	ASSERT_EQUAL(1.0_mps, 2.23694_mph);
}

void testSelfEquality() {
	ASSERT_EQUAL(1.0_kph, 1.0_kph);
}



bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(overtakePedestrianAt10Kph));
	s.push_back(CUTE(overtakePedestrianAt6dot2Mph));
	s.push_back(CUTE(overtakePedestrianAt2dot8Mps));
	s.push_back(CUTE(testConversionFromKphToMph));
	s.push_back(CUTE(testConversionFromMphToKph));
	s.push_back(CUTE(testConversionFromKphToMps));
	s.push_back(CUTE(testConversionFromMpsToKph));
	s.push_back(CUTE(testConversionFromMphToMps));
	s.push_back(CUTE(testConversionFromMpsToMph));
	s.push_back(CUTE(testSelfEquality));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
