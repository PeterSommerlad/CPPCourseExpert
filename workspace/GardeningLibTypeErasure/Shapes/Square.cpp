#include "Square.h"
#include <stdexcept>
#include <ostream>

namespace Gardening {
std::ostream &operator<<(std::ostream &out,Square const &c){
  return  out << Square::name << " " << pegs(c) << " " << ropes(c) << " " << area(c);
}

Square::Square(double const side)
    : side { side } {
	if (side <= 0.0) {
		throw std::invalid_argument{"Side length of a square must not be zero or below."};
	}
}

}
