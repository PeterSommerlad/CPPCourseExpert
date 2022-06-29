#include "TestCopyAssignUnicorn.h"
#include "CreateFreddy.h"
#include "Unicorn.h"

#include "cute.h"

#include <string>

void testCopyAssignUnicorn() {
	using namespace std::string_literals;
	auto const freddy = createFreddy();
	Unicorn other { "henry"s, "blue"s };
	other = freddy;
	ASSERT_EQUAL(freddy, other);
}
