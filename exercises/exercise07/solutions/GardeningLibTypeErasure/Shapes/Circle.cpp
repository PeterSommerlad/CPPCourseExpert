#include "Circle.h"
#include <stdexcept>
#include <string>
#include <numbers>
#include <ostream>

namespace Gardening {


std::ostream &operator<<(std::ostream &out,Circle const &c){
  return  out << Circle::name << " " << pegs(c) << " " << ropes(c) << " " << area(c);
}


double area(Circle const &c)  {
	return c.radius * c.radius * std::numbers::pi;
}

double ropes(Circle const &c)  {
	double const ropeForConstruction = c.radius;
	double const perimeter { 2 * c.radius * std::numbers::pi};
	return perimeter + ropeForConstruction;
}

}
