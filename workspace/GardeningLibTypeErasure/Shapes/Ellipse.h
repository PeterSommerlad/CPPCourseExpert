#ifndef ELLIPSE_H_
#define ELLIPSE_H_

#include <string>
#include <iosfwd>

namespace Gardening {

struct Ellipse {
	constexpr static inline unsigned const requiredPegs{2};
	static inline std::string const name{ "Ellipse" } ;

	Ellipse(double semiMajorAxis, double semiMinorAxis);
	friend unsigned pegs(Ellipse const &) { return Ellipse::requiredPegs;}
	friend double ropes(Ellipse const &e) ;
	friend double area(Ellipse const &e) ;
  friend
  std::ostream &operator<<(std::ostream &out, Ellipse const &c);


private:
	double semiMajorAxis;
	double semiMinorAxis;
};

}

#endif /* ELLIPSE_H_ */
