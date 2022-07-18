#include "Rectangle.h"
#include <stdexcept>
#include <ostream>
namespace Gardening {

std::ostream &operator<<(std::ostream &out,Rectangle const &c){
  return  out << Rectangle::name << " " << pegs(c) << " " << ropes(c) << " " << area(c);
}

Rectangle::Rectangle(double sideA, double sideB) :
		sideA { sideA }, sideB { sideB } {
	if (sideA <= 0.0 || sideB <= 0.0) {
		throw std::invalid_argument{"Side lengths of a rectangle must not be zero or below."};
	}
}



}
