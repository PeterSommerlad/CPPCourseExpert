#include "suite.h"
#include "cute.h"

void thisIsAsuiteTest() {
	ASSERTM("start writing tests", false);	
}

cute::suite make_suite_suite() {
	cute::suite s { };
	s.push_back(CUTE(thisIsAsuiteTest));
	return s;
}
