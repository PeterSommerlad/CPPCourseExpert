#include "Unicorn.h"

#include <cstddef>

#include <ostream>
#include <string>
#include <utility>

struct UnicornImpl {
	UnicornImpl(std::string name, std::string color) :
			m_name { std::move(name) }, m_color { std::move(color) } {
	}

	void glitter(std::ostream & out) const {
		out << m_name << " glitters beautifully\n";
	}

	void fly(std::ostream & out) const {
		out << m_name << " flies at " << calculateAltitude() << "m\n";
	}

	bool operator==(UnicornImpl const & other) const {
		return m_name == other.m_name && m_color == other.m_color;
	}

private:
	std::size_t calculateAltitude() const {
		return 8 * m_color.size();
	}

	std::string const m_name { };
	std::string const m_color { };
};

bool Unicorn::operator==(Unicorn const & other) const {
	return *pimpl == *other.pimpl;
}

bool Unicorn::operator!=(Unicorn const & other) const {
	return !(*this == other);
}

Unicorn::Unicorn(std::string name, std::string color) :
		pimpl { makeUniquePimpl<UnicornImpl>(std::move(name), std::move(color))} {
}

void Unicorn::glitter(std::ostream & out) const {
	pimpl->glitter(out);
}

void Unicorn::fly(std::ostream & out) const {
	pimpl->fly(out);
}
