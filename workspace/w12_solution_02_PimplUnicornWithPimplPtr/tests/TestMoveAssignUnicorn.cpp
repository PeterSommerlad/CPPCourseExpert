#include "TestMoveAssignUnicorn.h"

#include <Unicorn.h>

#include "CreateFreddy.h"
#include "cute.h"

#include <string>
#include <utility>


void testMoveAssignUnicorn() {
	using namespace std::string_literals;
	auto freddy = createFreddy();
	Unicorn other { "henry", "blue" };
	other = std::move(freddy);
	ASSERT_EQUAL(createFreddy(), other);
}
