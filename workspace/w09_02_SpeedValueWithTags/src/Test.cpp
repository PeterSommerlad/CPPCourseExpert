#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "Speed.h"

using velocity::Speed;
using namespace velocity::tags;

template <typename Unit>
bool isFasterThanWalking(Speed<Unit> speed) {
	return velocity::speedCast<Kph>(speed) > Speed<Kph>{5.0};
}

void overtakePedestrianAt10Kph() {
	ASSERT(isFasterThanWalking(Speed<Kph>{10.0}));
}

void overtakePedestrianAt6dot2Mph(){
	ASSERT(isFasterThanWalking(Speed<Mph>{6.2}));
}

void overtakePedestrianAt2dot8Mps(){
	ASSERT(isFasterThanWalking(Speed<Mps>{2.8}));
}


void testConversionFromKphToMph() {
	ASSERT_EQUAL(Speed<Kph>{1.60934}, Speed<Mph>{1.0});
}

void testConversionFromMphToKph() {
	ASSERT_EQUAL(Speed<Mph>{1.0}, Speed<Kph>{1.60934});
}

void testConversionFromKphToMps() {
	ASSERT_EQUAL(Speed<Kph>{3.6}, Speed<Mps>{1.0});
}

void testConversionFromMpsToKph() {
	ASSERT_EQUAL(Speed<Mps>{1.0}, Speed<Kph>{3.6});
}

void testConversionFromMphToMps() {
	ASSERT_EQUAL(Speed<Mph>{2.23694}, Speed<Mps>{1.0});
}

void testConversionFromMpsToMph() {
	ASSERT_EQUAL(Speed<Mps>{1.0}, Speed<Mph>{2.23694});
}

void testSelfEquality() {
	ASSERT_EQUAL(Speed<Kph>{1.0}, Speed<Kph>{1.0});
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
