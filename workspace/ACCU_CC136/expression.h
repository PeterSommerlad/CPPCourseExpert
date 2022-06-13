#ifndef EXPRESSION_H_
#define EXPRESSION_H_
#include <iosfwd>
#include <optional>

enum class operation : char {
  err,
  res = '=',
  add = '+',
  sub = '-',
  mul = '*',
  div = '/'
} ;

std::optional<double> readNumber(std::istream&);
operation readOperation(std::istream&);
std::istream &clearAndSkipToNewline(std::istream &);
std::optional<double> apply(double, operation, std::optional<double>);
void interaction(std::istream &in, std::ostream &out);

#endif /* EXPRESSION_H_ */
