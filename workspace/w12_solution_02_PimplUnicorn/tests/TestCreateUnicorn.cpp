#include <Unicorn.h>
#include "TestCreateUnicorn.h"
#include "CreateFreddy.h"
#include "cute.h"


void testCreateUnicorn() {
	Unicorn const freddy = createFreddy();
	ASSERT_EQUAL(freddy, freddy);
}
