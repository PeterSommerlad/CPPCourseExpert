#ifndef EXPRESSION_H_
#define EXPRESSION_H_

namespace hack { // Why is 'hack' needed?
typedef enum {
  add = '+',
  sub = '-',
  mul = '*',
  div = '/'
} operation;
}
using namespace hack;

double apply(double, operation, double);



#endif /* EXPRESSION_H_ */
