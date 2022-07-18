#include "Shape.h"
#include "AllShapes.h"
#include <ostream>
#include <string>
#include <type_traits>
namespace Gardening{

constexpr double seedPerSquareMeter { 0.1 };

unsigned Pegs(Shape const&s) {
  return std::visit([](auto const &ss){ return pegs(ss);},s);
}
double Ropes(Shape const &s) {
  return std::visit([](auto const &ss){ return ropes(ss);},s);
}
double Seeds(Shape const &s) {
  return std::visit([](auto const &ss){ return  seedPerSquareMeter * area(ss);},s);
}
std::string Name(Shape const &s) {
  return std::visit([](auto const &ss){
    return std::remove_reference_t<decltype(ss)>::name;
  },s);
}

void Print(std::ostream & out, Shape const &s)  {
	out << Name(s) << " " << Pegs(s) << " " << Ropes(s) << " " << Seeds(s);
}
}
