#include "DiamondSuite.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Shapes/Diamond.h"


namespace {

void simpleDiamondPrint() {
	Gardening::Diamond bed(1.0, 60.0);
	std::ostringstream result { };
	result<<bed;
	ASSERT_EQUAL("Diamond 4 4 0.866025", result.str());
}

void simpleDiamondPegs() {
	Gardening::Diamond bed(1.0, 60.0);
	ASSERT_EQUAL(4, pegs(bed));
}

void simpleDiamondRopes() {
	Gardening::Diamond bed(1.0, 60.0);
	ASSERT_EQUAL(4.0, ropes(bed));
}

void simpleDiamondarea() {
	Gardening::Diamond bed(1.0, 60.0);
	ASSERT_EQUAL_DELTA(0.866, area(bed), 0.001);
}

void negativeSize() {
	ASSERT_THROWS(Gardening::Diamond(-1.0, 60.0), std::invalid_argument);
}

void zeroSize() {
	ASSERT_THROWS(Gardening::Diamond(0.0, 60.0), std::invalid_argument);
}

void negaiveAngle() {
	ASSERT_THROWS(Gardening::Diamond(1.0, -60.0), std::invalid_argument);
}

void zeroAngle() {
	ASSERT_THROWS(Gardening::Diamond(1.0, 0.0), std::invalid_argument);
}

void halfcircleAngle() {
	ASSERT_THROWS(Gardening::Diamond(1.0, 180.0), std::invalid_argument);
}

void tooLargeAngle() {
	ASSERT_THROWS(Gardening::Diamond(1.0, 250.0), std::invalid_argument);
}

void smallAnglearea() {
	Gardening::Diamond bed(1.0, 0.5);
	ASSERT_EQUAL_DELTA(0.0087, area(bed), 0.0001);
}

void largeAnglearea() {
	Gardening::Diamond bed(1.0, 179.5);
	ASSERT_EQUAL_DELTA(0.0087, area(bed), 0.0001);
}

void rightAnglearea() {
	Gardening::Diamond bed(1.0, 90);
	ASSERT_EQUAL_DELTA(1., area(bed), 0.0001);
}

void smallDiamondRopes() {
	Gardening::Diamond bed(0.1, 60.0);
	ASSERT_EQUAL(0.4, ropes(bed));
}

void smallDiamondarea() {
	Gardening::Diamond bed(0.1, 60.0);
	ASSERT_EQUAL_DELTA(0.0087, area(bed), 0.0001);
}

void largeDiamondRopes() {
	Gardening::Diamond bed(150, 60.0);
	ASSERT_EQUAL(600.0, ropes(bed));
}

void largeDiamondarea() {
	Gardening::Diamond bed(150, 60.0);
	ASSERT_EQUAL_DELTA(19485.6, area(bed), 0.1);
}
}

cute::suite make_suite_DiamondSuite(){
	cute::suite s;
	s.push_back(CUTE(simpleDiamondPrint));
	s.push_back(CUTE(simpleDiamondPegs));
	s.push_back(CUTE(simpleDiamondRopes));
	s.push_back(CUTE(smallDiamondRopes));
	s.push_back(CUTE(largeDiamondRopes));
	s.push_back(CUTE(simpleDiamondarea));
	s.push_back(CUTE(smallDiamondarea));
	s.push_back(CUTE(largeDiamondarea));
	s.push_back(CUTE(negativeSize));
	s.push_back(CUTE(zeroSize));
	s.push_back(CUTE(negaiveAngle));
	s.push_back(CUTE(zeroAngle));
	s.push_back(CUTE(halfcircleAngle));
	s.push_back(CUTE(tooLargeAngle));
	s.push_back(CUTE(smallAnglearea));
	s.push_back(CUTE(largeAnglearea));
	s.push_back(CUTE(rightAnglearea));
	return s;
}



