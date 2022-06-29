#include "TestCopyConstructUnicorn.h"
#include "CreateFreddy.h"
#include "Unicorn.h"

#include "cute.h"

void testCopyConstructUnicorn() {
	auto const freddy = createFreddy();
	auto const copy { freddy };
	ASSERT_EQUAL(freddy, copy);
}
