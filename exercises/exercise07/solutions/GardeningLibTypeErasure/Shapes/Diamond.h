#ifndef DIAMOND_H_
#define DIAMOND_H_

#include <string>
#include <iosfwd>
namespace Gardening {

struct Diamond {
	constexpr static inline unsigned  requiredPegs{ 4 } ;
	constexpr static inline unsigned  numberOfSides{ 4 } ;
	constexpr static inline double degreesOfHalfcircle { 180.0 };
	static inline std::string const name{ "Diamond" };

	Diamond(double sideLength, double angleDegrees);
	friend unsigned pegs(Diamond const &) { return Diamond::requiredPegs; }
	friend double ropes(Diamond const &d) { return d.numberOfSides * d.sideLength;}

	friend double area(Diamond const &c) ;
  friend
  std::ostream &operator<<(std::ostream &out,Diamond const &c);

private:
	double const sideLength;
	double const angle;


};

}

#endif /* DIAMOND_H_ */
