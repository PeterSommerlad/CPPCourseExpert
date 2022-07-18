#include "Triangle.h"

#include <algorithm>
#include <stdexcept>
#include <cmath>

#include <ostream>

namespace Gardening {


std::ostream &operator<<(std::ostream &out,Triangle const &c){
  return  out << Triangle::name << " " << pegs(c) << " " << ropes(c) << " " << area(c);
}

Triangle::Triangle(double sideA, double sideB, double sideC) :
		 sideA { sideA }, sideB { sideB }, sideC { sideC } {
	if (!checkTriangleInput()) {
		throw std::invalid_argument{"Side lengths do not form a proper triangle."};
	}
}

bool Triangle::checkTriangleInput() const {
	if (sideA <= 0.0 || sideB < 0.0 || sideC < 0.0) {
		return false;
	}
	double const longestSide = std::max({sideA, sideB, sideC});
	return sideA + sideB + sideC > 2 * longestSide;
}



double area(Triangle const &t)  {
	//Heron
	double const semiperimeter { t.perimeter() / 2 };
	double const area = std::sqrt(semiperimeter
	                              * (semiperimeter - t.sideA)
	                              * (semiperimeter - t.sideB)
	                              * (semiperimeter - t.sideC));
	return area;
}

double Triangle::perimeter() const {
	return sideA + sideB + sideC;
}

}
