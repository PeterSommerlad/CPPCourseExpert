#include <Unicorn.h>
#include "CreateFreddy.h"
#include <string>

Unicorn createFreddy() {
	using namespace std::string_literals;
	Unicorn freddy { "freddy"s, "red"s };
	return freddy;
}
