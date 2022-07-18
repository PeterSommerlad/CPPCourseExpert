#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <string>
#include <iosfwd>

namespace Gardening {

struct Rectangle {
	constexpr static inline unsigned  requiredPegs{4};
	static inline std::string const name{"Rectangle"};

	Rectangle(double sideA, double sideB);

	friend unsigned pegs(Rectangle const&) {return Rectangle::requiredPegs;}
	friend double ropes(Rectangle const &r) {return 2 * (r.sideA + r.sideB);}
	friend double area(Rectangle const &r) { return r.sideA * r.sideB ; }
  friend std::string name(Rectangle const &c) { return Rectangle::name; }
  friend
  std::ostream &operator<<(std::ostream &out,Rectangle const &c);


private:
	double  sideA;
	double  sideB;
};

}

#endif /* RECTANGLE_H_ */
