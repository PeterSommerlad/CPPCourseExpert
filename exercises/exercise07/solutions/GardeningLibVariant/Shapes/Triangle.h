#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <string>
#include <iosfwd>

namespace Gardening {

struct Triangle {
  constexpr static inline unsigned  requiredPegs{3};
  static inline std::string const name{"Triangle"};

	Triangle(double sideA, double sideB, double sideC);

  friend unsigned pegs(Triangle const&) {return Triangle::requiredPegs;}
  friend double ropes(Triangle const &r) {return r.perimeter();}
  friend double area(Triangle const &r) ;
  friend
  std::ostream &operator<<(std::ostream &out, Triangle const &c);

private:
	double sideA;
	double sideB;
	double sideC;
	bool checkTriangleInput() const;
	double perimeter() const;
};

}

#endif /* TRIANGLE_H_ */
