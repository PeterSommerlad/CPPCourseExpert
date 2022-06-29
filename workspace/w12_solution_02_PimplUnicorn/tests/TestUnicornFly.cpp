#include <Unicorn.h>
#include "TestUnicornFly.h"
#include "CreateFreddy.h"
#include "cute.h"

#include <sstream>
#include <string>

void testUnicornFly() {
	using namespace std::string_literals;
	auto const freddy = createFreddy();
	std::ostringstream out { };
	freddy.fly(out);
	ASSERT_EQUAL("freddy flies at 24m\n"s, out.str());
}
