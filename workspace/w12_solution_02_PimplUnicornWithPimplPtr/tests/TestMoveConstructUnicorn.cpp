#include "TestMoveConstructUnicorn.h"

#include <Unicorn.h>

#include "CreateFreddy.h"
#include "cute.h"

#include <utility>


void testMoveConstructUnicorn() {
	auto freddy = createFreddy();
	auto moved { std::move(freddy) };
	ASSERT_EQUAL(createFreddy(), moved);
}
