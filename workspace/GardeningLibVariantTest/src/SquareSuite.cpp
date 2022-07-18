#include "SquareSuite.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Shapes/Square.h"
#include<stdexcept>

namespace {

void simpleSquarePrint() {
	Gardening::Square bed(2.0);
	std::ostringstream result { };
  result << bed;
	ASSERT_EQUAL("Square 4 8 4", result.str());
}

void simpleSquarePegs() {
	Gardening::Square bed(2.0);
	ASSERT_EQUAL(4, pegs(bed));
}

void simpleSquareRopes() {
	Gardening::Square bed(2.0);
	ASSERT_EQUAL(8.0, ropes(bed));
}

void simpleSquarearea() {
	Gardening::Square bed(2.0);
	ASSERT_EQUAL(4, area(bed));
}

void negativeSideLength() {
	ASSERT_THROWS(Gardening::Square(-1.0), std::invalid_argument);
}

void zeroSideLength() {
	ASSERT_THROWS(Gardening::Square(0.0), std::invalid_argument);
}

void smallSquareRopes(){
	Gardening::Square bed(0.1);
	ASSERT_EQUAL(0.4, ropes(bed));
}

void smallSquarearea(){
	Gardening::Square bed(0.1);
	ASSERT_EQUAL(0.01, area(bed));
}

void largeSquareRopes(){
	Gardening::Square bed(125.8);
	ASSERT_EQUAL(503.2, ropes(bed));
}

void largeSquarearea(){
	Gardening::Square bed(125.8);
	ASSERT_EQUAL(15825.64, area(bed));
}

void fractionalSideLengthRopes(){
	Gardening::Square bed(1.0/3.0);
	ASSERT_EQUAL_DELTA(4.0/3.0, ropes(bed), 0.001);
}

void fractionalSideLengtharea(){
	Gardening::Square bed(1.0/3.0);
	ASSERT_EQUAL_DELTA(1/9.0, area(bed), 0.001);
}
}

cute::suite make_suite_SquareSuite(){
	cute::suite s;
	s.push_back(CUTE(simpleSquarePrint));
	s.push_back(CUTE(simpleSquarePegs));
	s.push_back(CUTE(simpleSquareRopes));
	s.push_back(CUTE(smallSquareRopes));
	s.push_back(CUTE(largeSquareRopes));
	s.push_back(CUTE(fractionalSideLengthRopes));
	s.push_back(CUTE(simpleSquarearea));
	s.push_back(CUTE(smallSquarearea));
	s.push_back(CUTE(largeSquarearea));
	s.push_back(CUTE(fractionalSideLengtharea));
	s.push_back(CUTE(negativeSideLength));
	s.push_back(CUTE(zeroSideLength));
	return s;
}



