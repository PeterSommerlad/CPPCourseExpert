#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "Temperature.h"

using units::Temperature;
using namespace units::tags;
using namespace units::literals;


template <typename scale>
constexpr bool willWaterFreeze(Temperature<scale> const & temperature) {
	return units::temperatureCast<Celcius>(temperature) <= Temperature<Celcius>{0.0};
}

void waterFreezesAt273Kelvin() {
	ASSERT(willWaterFreeze(Temperature<Kelvin>{273}));
}

void waterFreezesAt0Celcius(){
	ASSERT(willWaterFreeze(Temperature<Celcius>{0}));
}

void waterFreezesAt32Fahrenheit(){
	ASSERT(willWaterFreeze(Temperature<Fahrenheit>{32}));
}

void testCelciusToKelvin() {
	static_assert(20_C == 293.15_K);
	ASSERT_EQUAL(20_C, 293.15_K);
}

void testKelvinToCelcius() {
	static_assert(20_K == -253.15_C);
	ASSERT_EQUAL(20_K, -253.15_C);
}

void testFahrenheitToCelcius() {
	static_assert(20_F == -6.6667_C);
	ASSERT_EQUAL(20_F, -6.6667_C);
}

void testCelciusToFahrenheit() {
	static_assert(20_C == 68.0_F);
	ASSERT_EQUAL(20_C, 68.0_F);
}

void testKelvinToFahrenheit() {
	static_assert(20_K == -423.67_F);
	ASSERT_EQUAL(20_K, -423.67_F);
}

void testFahrenheitToKelvin() {
	static_assert(20_F == 266.4833_K);
	ASSERT_EQUAL(20_F, 266.4833_K);
}



bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(waterFreezesAt273Kelvin));
	s.push_back(CUTE(waterFreezesAt0Celcius));
	s.push_back(CUTE(waterFreezesAt32Fahrenheit));
	s.push_back(CUTE(testCelciusToKelvin));
	s.push_back(CUTE(testKelvinToCelcius));
	s.push_back(CUTE(testFahrenheitToCelcius));
	s.push_back(CUTE(testCelciusToFahrenheit));
	s.push_back(CUTE(testKelvinToFahrenheit));
	s.push_back(CUTE(testFahrenheitToKelvin));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
