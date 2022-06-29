#ifndef UNICORN
#define UNICORN

#include "PimplPtr.h"

#include <string>

struct Unicorn {
  Unicorn(std::string name, std::string color);

  void glitter(std::ostream & out) const;

  void fly(std::ostream & out) const;

  bool operator==(Unicorn const & other) const;
  bool operator!=(Unicorn const & other) const;

private:
  PimplPtr<class UnicornImpl> pimpl;
};


#endif
