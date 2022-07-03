#include <iostream>
#include <cstddef>
#include <string>

namespace mystring {

inline std::string operator"" _s(char const *s, std::size_t len) {
	return std::string { s, len };
}

inline std::string operator"" _s(char const *s) {
  return std::string { s };
}

}


int main(int argc, char **argv) {
	using namespace mystring;
	auto s = "hello"_s;
	s += " world\n";
	std::cout << s;

	auto rs = 42_s;
	rs += " raw\n";
	std::cout << rs;
}
