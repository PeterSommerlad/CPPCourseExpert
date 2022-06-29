#include <Unicorn.h>
#include <ostream>
#include <string>
#include <utility>

Unicorn::Unicorn(std::string name, std::string color) :
  m_name{std::move(name)}, m_color{std::move(color)} {}

void Unicorn::glitter(std::ostream & out) const {
  out << m_name << " glitters beautifully\n";
}

void Unicorn::fly(std::ostream & out) const {
  out << m_name << " flies at " << calculateAltitude() << "m\n";
}

bool Unicorn::operator==(Unicorn const & other) const {
	return m_name == other.m_name && m_color == other.m_color;
}
bool Unicorn::operator!=(Unicorn const & other) const {
	return !(*this == other);
}

int Unicorn::calculateAltitude() const {
  return 8 * m_color.size();
}
