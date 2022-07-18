#ifndef CIRCLE_H_
#define CIRCLE_H_

#include <stdexcept>
#include <string>
#include <iosfwd>
namespace Gardening {

struct Circle  {
	constexpr static inline unsigned  requiredPegs {1};
	static inline std::string const name{ "Circle" };
  explicit Circle(double const x)
  : radius { x } {
    if (x <= 0) throw std::invalid_argument{"Radius must not be zero or below."};
  }
  friend unsigned pegs(Circle const &c) { return Circle::requiredPegs; }
  friend double ropes(Circle const &c) ;
  friend double area(Circle const &c) ;
  friend
  std::ostream &operator<<(std::ostream &out,Circle const &c);

private:
	double const radius;
};



}

#endif /* CIRCLE_H_ */
