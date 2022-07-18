#include "Diamond.h"
#include <cmath>
#include <stdexcept>
#include <numbers>
#include <ostream>

namespace Gardening {

std::ostream &operator<<(std::ostream &out,Diamond const &d){
  return  out << Diamond::name << " " << pegs(d) << " " << ropes(d) << " " << area(d);
}

static constexpr double convertToRad(double degrees){
  return degrees * std::numbers::pi / 180;
}
Diamond::Diamond(double sideLength, double angleDegrees) :
		sideLength { sideLength }, angle { convertToRad(angleDegrees) } {
	if (angleDegrees <= 0.0 || angleDegrees >= degreesOfHalfcircle) {
		throw std::invalid_argument{"The angle of a diamond must be between 0 and 180 degrees."};
	}
	if (sideLength <= 0.0) {
		throw std::invalid_argument{"Side length of a diamond must not be zero or below."};
	}
}



double area(Diamond const &d)  {
	return d.sideLength * d.sideLength * std::sin(d.angle) ;
}

}
