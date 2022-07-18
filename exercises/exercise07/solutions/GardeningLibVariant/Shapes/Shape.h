#ifndef SHAPE_H_
#define SHAPE_H_

#include <iosfwd>
#include <string>
#include <variant>
namespace Gardening {
struct Circle;
struct Diamond;
struct Ellipse;
struct Rectangle;
struct Square;
struct Triangle;
using Shape = std::variant<Circle, Diamond, Ellipse, Rectangle, Square, Triangle>;

void Print(std::ostream & out, Shape const &s) ;
unsigned Pegs(Shape const&) ;
double Ropes(Shape const &) ;
double Seeds(Shape const &);
std::string Name(Shape const &) ;


}

#endif /* SHAPE_H_ */
