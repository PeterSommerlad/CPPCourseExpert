#include "PolymorphismSuite.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Shapes.h"

#include <sstream>
#include <vector>

void printAllShapes(){
  using namespace Gardening;
  std::vector<Shape> const v {
    Circle{1.0},
    Diamond{1.0,60.0},
    Ellipse{2.0,3.0},
    Rectangle{1.0,2.0},
    Square{2.0},
    Triangle{1.0,1.0,1.0}
  };
  std::ostringstream out{};
  for(auto const &s: v){
    Print(out,s);
    out << '\n';
  }
  ASSERT_EQUAL(R"(Circle 1 7.28319 0.314159
Diamond 4 4 0.0866025
Ellipse 2 23.019 1.88496
Rectangle 4 6 0.2
Square 4 8 0.4
Triangle 3 3 0.0433013
)",out.str());
}

namespace{

void circlePegs() {
	Gardening::Circle bed(1.0);
	Gardening::Shape  shape = bed;
	ASSERT_EQUAL(1, Pegs(shape));
}

void circleRopes(){
	Gardening::Circle bed(1.0);
	Gardening::Shape  shape = bed;
	ASSERT_EQUAL_DELTA(7.28, Ropes(shape), 0.01);
}

void circleSeeds(){
	Gardening::Circle bed(1.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL_DELTA(0.314, Seeds(shape), 0.001);
}

void diamondPegs() {
	Gardening::Diamond bed(1.0, 60.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL(4, Pegs(shape));
}

void diamondRopes() {
	Gardening::Diamond bed(1.0, 60.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL(4.0, Ropes(shape));
}

void diamondSeeds() {
	Gardening::Diamond bed(1.0, 60.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL_DELTA(0.0866, Seeds(shape), 0.0001);
}

void simpleEllipsePegs() {
	Gardening::Ellipse bed(2.0, 1.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL(2, Pegs(shape));
}

void simpleEllipseRopes(){
	Gardening::Ellipse bed(2.0, 1.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL_DELTA(14.93, Ropes(shape), 0.01);
}

void simpleEllipseSeeds(){
	Gardening::Ellipse bed(2.0, 1.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL_DELTA(0.628, Seeds(shape), 0.001);
}

void rectanglePegs() {
	Gardening::Rectangle bed(2.0, 1.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL(4, Pegs(shape));
}

void rectangleRopes() {
	Gardening::Rectangle bed(2.0, 1.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL(6.0, Ropes(shape));
}

void rectangleSeeds() {
	Gardening::Rectangle bed(2.0, 1.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL(0.2, Seeds(shape));
}

void simpleSquarePegs() {
	Gardening::Square bed(2.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL(4, Pegs(shape));
}

void simpleSquareRopes() {
	Gardening::Square bed(2.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL(8.0, Ropes(shape));
}

void simpleSquareSeeds() {
	Gardening::Square bed(2.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL(0.4, Seeds(shape));
}

void trianglePegs() {
	Gardening::Triangle bed(1.0, 1.0, 1.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL(3, Pegs(shape));
}

void triangleRopes() {
	Gardening::Triangle bed(1.0, 1.0, 1.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL(3.0, Ropes(shape));
}

void triangleSeeds() {
	Gardening::Triangle bed(1.0, 1.0, 1.0);
	Gardening::Shape shape = bed;
	ASSERT_EQUAL_DELTA(0.0433, Seeds(shape), 0.0001);
}



}

cute::suite make_suite_PolymorphismSuite(){
	cute::suite s;
	s.push_back(CUTE(circlePegs));
	s.push_back(CUTE(circleRopes));
	s.push_back(CUTE(circleSeeds));
	s.push_back(CUTE(diamondPegs));
	s.push_back(CUTE(diamondRopes));
	s.push_back(CUTE(diamondSeeds));
	s.push_back(CUTE(simpleEllipsePegs));
	s.push_back(CUTE(simpleEllipseRopes));
	s.push_back(CUTE(simpleEllipseSeeds));
	s.push_back(CUTE(rectanglePegs));
	s.push_back(CUTE(rectangleRopes));
	s.push_back(CUTE(rectangleSeeds));
	s.push_back(CUTE(simpleSquarePegs));
	s.push_back(CUTE(simpleSquareRopes));
	s.push_back(CUTE(simpleSquareSeeds));
	s.push_back(CUTE(trianglePegs));
	s.push_back(CUTE(triangleRopes));
	s.push_back(CUTE(triangleSeeds));

  s.push_back(CUTE(printAllShapes));

	return s;
}



