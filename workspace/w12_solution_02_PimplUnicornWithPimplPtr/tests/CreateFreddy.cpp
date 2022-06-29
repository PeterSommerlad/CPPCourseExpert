#include "CreateFreddy.h"
#include <string>
#include "../Unicorn.h"

Unicorn createFreddy() {
	using namespace std::string_literals;
	Unicorn freddy { "freddy"s, "red"s };
	return freddy;
}
