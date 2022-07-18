#ifndef SQUARE_H_
#define SQUARE_H_

#include <string>
#include <iosfwd>

namespace Gardening {

struct Square  {
  constexpr static inline unsigned  requiredPegs{4};
	static inline std::string const name{"Square"};

	explicit Square(double side);

  friend unsigned pegs(Square const&) {return Square::requiredPegs;}
  friend double ropes(Square const &r) {return 4 * r.side;}
  friend double area(Square const &r) { return r.side * r.side ; }
  friend
  std::ostream &operator<<(std::ostream &out,Square const &c);

private:
	double  side;
};

}

#endif /* SQUARE_H_ */
