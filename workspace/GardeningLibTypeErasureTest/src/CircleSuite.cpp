#include "CircleSuite.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Shapes/Circle.h"
#include<string>
#include<sstream>

namespace{


void simpleCirclePrint() {
	Gardening::Circle bed(1.0);
	std::ostringstream result;
	result<<bed;
	ASSERT_EQUAL("Circle 1 7.28319 3.14159", result.str());
}

void simpleCirclePegs() {
	Gardening::Circle bed(1.0);
	ASSERT_EQUAL(1, pegs(bed));
}

void simpleCircleRopes(){
	Gardening::Circle bed(1.0);
	ASSERT_EQUAL_DELTA(7.28, ropes(bed), 0.01);
}

void smallCircleRopes(){
	Gardening::Circle bed(0.2);
	ASSERT_EQUAL_DELTA(1.45, ropes(bed), 0.01);
}

void largeCircleRopes(){
	Gardening::Circle bed(157.3);
	ASSERT_EQUAL_DELTA(1145.6, ropes(bed), 0.1);
}

void simpleCircleArea(){
	Gardening::Circle bed(1.0);
	ASSERT_EQUAL_DELTA(3.141, area(bed), 0.001);
}

void smallCircleArea(){
	Gardening::Circle bed(0.2);
	ASSERT_EQUAL_DELTA(0.125, area(bed), 0.001);
}

void largeCircleArea(){
	Gardening::Circle bed(157.3);
	ASSERT_EQUAL_DELTA(77733.3, area(bed), 0.1);
}

void zeroRadius() {
	ASSERT_THROWS(Gardening::Circle(0.0), std::invalid_argument);
}

void negativeRadius() {
	ASSERT_THROWS(Gardening::Circle(-2.5), std::invalid_argument);
}

}

cute::suite make_suite_CircleSuite(){
	cute::suite s;
	s.push_back(CUTE(simpleCirclePrint));
	s.push_back(CUTE(simpleCirclePegs));
	s.push_back(CUTE(simpleCircleRopes));
	s.push_back(CUTE(smallCircleRopes));
	s.push_back(CUTE(largeCircleRopes));
	s.push_back(CUTE(simpleCircleArea));
	s.push_back(CUTE(smallCircleArea));
	s.push_back(CUTE(largeCircleArea));
	s.push_back(CUTE(zeroRadius));
	s.push_back(CUTE(negativeRadius));

	return s;
}



