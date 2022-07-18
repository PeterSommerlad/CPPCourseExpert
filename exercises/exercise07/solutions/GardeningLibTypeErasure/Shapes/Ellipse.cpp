#include "Ellipse.h"
#include <cmath>
#include <stdexcept>
#include <numbers>
#include <ostream>

namespace Gardening {
std::ostream &operator<<(std::ostream &out,Ellipse const &e){
  return  out << Ellipse::name << " " << pegs(e) << " " << ropes(e) << " " << area(e);
}

Ellipse::Ellipse(double semiMajorAxis, double semiMinorAxis) :
		semiMajorAxis { semiMajorAxis }, semiMinorAxis { semiMinorAxis } {
	if (semiMajorAxis <= 0.0 || semiMinorAxis <= 0.0) {
		throw std::invalid_argument{"Semiaxes of an ellipse must not be zero or below."};
	}
	if (semiMajorAxis < semiMinorAxis) {
	  std::swap(semiMajorAxis,semiMinorAxis);
	}
}


double ropes(Ellipse const &e)  {
	//Gaertnerkonstruktion (http://de.wikipedia.org/wiki/G%C3%A4rtnerkonstruktion)
  // https://en.wikipedia.org/wiki/Ellipse#Pins-and-string_method
  double const ropeForConstruction { e.semiMinorAxis + 2 * e.semiMajorAxis };
	//Approximation of perimeter: ~10% accuracy (http://de.wikipedia.org/wiki/Ellipse#Umfang)
	double const perimeter { std::numbers::pi * std::sqrt(2 * (e.semiMajorAxis * e.semiMajorAxis + e.semiMinorAxis * e.semiMinorAxis)) };
	return perimeter + ropeForConstruction;
}

double area(Ellipse const &e)  {
	return std::numbers::pi * e.semiMajorAxis * e.semiMinorAxis;
}

}
