#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "TestCopyAssignUnicorn.h"
#include "TestCopyConstructUnicorn.h"
#include "TestCreateUnicorn.h"
#include "TestMoveAssignUnicorn.h"
#include "TestMoveConstructUnicorn.h"
#include "TestUnicornFly.h"
#include "TestUnicornGlitter.h"



bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testUnicornFly));
	s.push_back(CUTE(testUnicornGlitter));
	s.push_back(CUTE(testCreateUnicorn));
	s.push_back(CUTE(testCopyConstructUnicorn));
	s.push_back(CUTE(testMoveConstructUnicorn));
	s.push_back(CUTE(testCopyAssignUnicorn));
	s.push_back(CUTE(testMoveAssignUnicorn));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
