#include "TestUnicornGlitter.h"

#include <Unicorn.h>

#include "CreateFreddy.h"
#include "cute.h"

#include <sstream>
#include <string>


void testUnicornGlitter() {
	using namespace std::string_literals;
	auto const freddy = createFreddy();
	std::ostringstream out{};
	freddy.glitter(out);
	ASSERT_EQUAL("freddy glitters beautifully\n"s, out.str());
}
