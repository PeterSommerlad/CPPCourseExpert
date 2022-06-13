#include "expression.h"

#include <istream>
#include <optional>
#include <ostream>
#include <string_view>

std::optional<double> apply(double const lhs,
                            operation const oper,
                            std::optional<double> rhs) {
    using enum operation;
    switch (oper) {
    case res:
        [[fallthrough]];
    case err:
        return rhs;
    case add:
        return rhs ?  lhs + *rhs  : rhs;
    case sub:
        return rhs ?  lhs - *rhs  : rhs;
    case mul:
        return rhs ?  lhs * *rhs  : rhs;
    case div:
        return rhs && *rhs ? lhs / *rhs : std::optional<double>{};
    }
    return {}; // some logic error occured
}
std::optional<double> readNumber(std::istream &in){
    double result{};
    if (in >> result){
        return result;
    }
    return {};
}
operation readOperation(std::istream &in){
    char ch{};
    constexpr std::string_view opers{"=+-*/"};
    if (in >> ch && std::string_view::npos != opers.find(ch)) {
        // c++23: in >> ch && opers.contains(ch)
        return static_cast<operation>(ch);
    }
    return {};
}
std::istream &clearAndSkipToNewline(std::istream &in){
    in.clear();
    while(in && in.get() != '\n');
    return in;
}
void handleResultOrError(double const result,
                         operation const oper,
                         std::istream &in,
                         std::ostream &out) {
    if (oper == operation::res) {
        out << "Result: " << result << '\n';
    } else if (oper == operation::err) {
        out << "invalid operator, restarting\n";
        clearAndSkipToNewline(in);
    }
}
void interaction(std::istream &in, std::ostream &out) {
    auto result = readNumber(in);
    while (not in.eof()){
        if (result){
            auto const oper = readOperation(in);
            handleResultOrError(*result, oper, in, out);
            result = apply(*result, oper, readNumber(in));
        } else {
            clearAndSkipToNewline(in);
            result = readNumber(in);
        }
    }
}
/* railroad diagram: https://www.xanthir.com/etc/railroad-diagrams/generator.html
 *
Diagram(
    NonTerminal('number'),
    Choice(1,Skip(),
     OneOrMore(
      Sequence(Choice( 0, '+' , '-', '*', '/' ),
        NonTerminal('number')))
   ),
   '='
)
 */
/* refactored diagram:
Diagram(
 OneOrMore(
  Sequence(
   NonTerminal('number'),
   Choice( 0,'=', '+' , '-', '*', '/' )
)))
 */

