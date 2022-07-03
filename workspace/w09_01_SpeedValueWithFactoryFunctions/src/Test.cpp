#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "Speed.h"

using velocity::Speed;

void overtakePedestrianAt10Kph() {
	ASSERT(isFasterThanWalking(Speed::fromKph(10.0)));
}

void overtakePedestrianAt6dot2Mph(){
	ASSERT(isFasterThanWalking(Speed::fromMph(6.2)));
}

void overtakePedestrianAt2dot8Mps(){
	ASSERT(isFasterThanWalking(Speed::fromMps(2.8)));
}

void testMpsLiteral() {
	using namespace velocity::literals;
	auto const speed = 5.0_mps;
	ASSERT_EQUAL(5.0, speed.toMps());
}
void testKpsLiteral() {
	using namespace velocity::literals;
	auto const speed = 5.0_kph;
	ASSERT_EQUAL(5.0, speed.toKph());
}
void testMphLiteral() {
	using namespace velocity::literals;
	auto const speed = 5.0_mph;
	ASSERT_EQUAL(5.0, speed.toMph());
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(overtakePedestrianAt10Kph));
	s.push_back(CUTE(overtakePedestrianAt6dot2Mph));
	s.push_back(CUTE(overtakePedestrianAt2dot8Mps));
	s.push_back(CUTE(testMpsLiteral));
	s.push_back(CUTE(testMphLiteral));
	s.push_back(CUTE(testKpsLiteral));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
