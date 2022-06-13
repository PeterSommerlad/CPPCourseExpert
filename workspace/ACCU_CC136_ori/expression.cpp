#include "expression.h"

double apply(double lhs, operation oper,
             double rhs) {
  switch (oper) {
  add:
    lhs += rhs;
  sub:
    lhs -= rhs;
  mult:
    lhs *= rhs;
  div:
    lhs /= rhs;
  default:;
  }
  return lhs;
}
