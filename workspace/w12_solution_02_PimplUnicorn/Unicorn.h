#ifndef UNICORN
#define UNICORN


#include <memory>
#include <string>

struct Unicorn {
  Unicorn(std::string name, std::string color);
  ~Unicorn();
  Unicorn(Unicorn &&);
  Unicorn & operator=(Unicorn &&);

  void glitter(std::ostream & out) const;

  void fly(std::ostream & out) const;

  bool operator==(Unicorn const & other) const;
  bool operator!=(Unicorn const & other) const;

private:
  std::unique_ptr<class UnicornImpl> pimpl;
};


#endif
