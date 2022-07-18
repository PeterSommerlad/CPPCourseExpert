#include "EllipseSuite.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Shapes/Ellipse.h"

namespace{

void simpleEllipsePrint() {
	Gardening::Ellipse bed(2.0, 1.0);
	std::ostringstream result { };
	result<<bed;
	ASSERT_EQUAL("Ellipse 2 14.9346 6.28319", result.str());
}

void simpleEllipsePegs() {
	Gardening::Ellipse bed(2.0, 1.0);
	ASSERT_EQUAL(2, pegs(bed));
}

void simpleEllipseRopes(){
	Gardening::Ellipse bed(2.0, 1.0);
	ASSERT_EQUAL_DELTA(14.93, ropes(bed), 0.01);
}

void smallEllipseRopes(){
	Gardening::Ellipse bed(0.5,0.3);
	ASSERT_EQUAL_DELTA(3.89, ropes(bed), 0.01);
}

void largeEllipseRopes(){
	Gardening::Ellipse bed(68.7, 35.9);
	ASSERT_EQUAL_DELTA(517.7, ropes(bed), 0.1);
}

void simpleEllipsearea(){
	Gardening::Ellipse bed(2.0, 1.0);
	ASSERT_EQUAL_DELTA(6.283, area(bed), 0.001);
}

void smallEllipsearea(){
	Gardening::Ellipse bed(0.5,0.3);
	ASSERT_EQUAL_DELTA(0.4712, area(bed), 0.001);
}

void largeEllipsearea(){
	Gardening::Ellipse bed(68.7, 35.9);
	ASSERT_EQUAL_DELTA(7748.2, area(bed), 0.1);
}
void largeEllipseareaFlippedAxes(){
  Gardening::Ellipse bed( 35.9, 68.7);
  ASSERT_EQUAL_DELTA(7748.2, area(bed), 0.1);
}

void zeroSemiMajorAxis() {
	ASSERT_THROWS(Gardening::Ellipse(0, 1.5), std::invalid_argument);
}

void negativeSemiMajorAxis() {
	ASSERT_THROWS(Gardening::Ellipse(-2.5, 1.5), std::invalid_argument);
}

void zeroSemiMinorAxis() {
	ASSERT_THROWS(Gardening::Ellipse(4.3, 0), std::invalid_argument);
}

void negativeSemiMinroAxis() {
	ASSERT_THROWS(Gardening::Ellipse(4.3, -2.8), std::invalid_argument);
}



}

cute::suite make_suite_EllipseSuite(){
	cute::suite s;
	s.push_back(CUTE(simpleEllipsePrint));
	s.push_back(CUTE(simpleEllipsePegs));
	s.push_back(CUTE(simpleEllipseRopes));
	s.push_back(CUTE(smallEllipseRopes));
	s.push_back(CUTE(largeEllipseRopes));
	s.push_back(CUTE(simpleEllipsearea));
	s.push_back(CUTE(smallEllipsearea));
	s.push_back(CUTE(largeEllipsearea));
	s.push_back(CUTE(zeroSemiMajorAxis));
	s.push_back(CUTE(negativeSemiMajorAxis));
	s.push_back(CUTE(zeroSemiMinorAxis));
	s.push_back(CUTE(negativeSemiMinroAxis));
	s.push_back(CUTE(largeEllipseareaFlippedAxes));
	return s;
}



