#ifndef UNICORN
#define UNICORN

#include <string>

struct Unicorn {
  Unicorn(std::string name, std::string color);

  void glitter(std::ostream & out) const;

  void fly(std::ostream & out) const;

  bool operator==(Unicorn const & other) const;
  bool operator!=(Unicorn const & other) const;

  private:
    int calculateAltitude() const;

    std::string m_name{};
    std::string m_color{};
};

#endif
