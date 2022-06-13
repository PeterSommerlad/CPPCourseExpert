#include "expression.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <sstream>

void Adding1plus1Istwo(){
	ASSERT_EQUAL(2., *apply(1.,operation::add,1.));
}
void Subtracting4From6Is2(){
    ASSERT_EQUAL(2., *apply(6.,operation::sub,4.));
}
void Multiply2By3Is6(){
    ASSERT_EQUAL(6., *apply(2.,operation::mul,3.));
}
void Divide6By3Is2(){
    ASSERT_EQUAL(2., *apply(6.,operation::div,3.));
}
void DivideByZEroDeliversNullOpt(){
    ASSERT( not apply(1.,operation::div,0));
}


void testReadNumberEmptyFails(){
    std::istringstream input{};
    auto maybenumber = readNumber(input);
    ASSERT(not maybenumber.has_value());
}
void testReadNumber(){
    std::istringstream input{" 3.14 "};
    auto maybenumber = readNumber(input);
    ASSERT_EQUAL(3.14, (maybenumber?*maybenumber:0.0));
}
void testReadNumberWithNonNumber(){
    std::istringstream input{"a 3.14 "};
    auto maybenumber = readNumber(input);
    ASSERT(not maybenumber.has_value());
}

void testReadOperationEmptyFails(){
    std::istringstream input{};
    ASSERT_EQUAL(operation::err, readOperation(input));
}
void testReadOperationInvalidSymbolFails(){
    std::istringstream input{" a "};
    ASSERT_EQUAL(operation::err, readOperation(input));
}
void testReadOperationResult(){
    std::istringstream input{" = "};
    ASSERT_EQUAL(operation::res, readOperation(input));
}
void testReadOperationAll(){
    std::istringstream input{" = + - * / %"};
    ASSERT_EQUAL(operation::res, readOperation(input));
    ASSERT_EQUAL(operation::add, readOperation(input));
    ASSERT_EQUAL(operation::sub, readOperation(input));
    ASSERT_EQUAL(operation::mul, readOperation(input));
    ASSERT_EQUAL(operation::div, readOperation(input));
    ASSERT_EQUAL(operation::err, readOperation(input));
}

void testSkipToNewlineEmpty(){
    std::istringstream input{" abc   "};
    clearAndSkipToNewline(input);
    ASSERT(input.eof());

}
void testSkipToNewline(){
    std::istringstream input{" 123a \n456"};
    input.setstate(std::ios_base::failbit);
    ASSERT(clearAndSkipToNewline(input));
    std::string s{};
    getline(input,s);
    ASSERT_EQUAL("456",s);
}
void testSkipToNewlineAsManipulator(){
    std::istringstream input{" 123a \n456"};
    input.setstate(std::ios_base::failbit);
    input >> clearAndSkipToNewline;
    std::string s{};
    getline(input,s);
    ASSERT_EQUAL("456",s);
}

void testSimpleAddition(){
    std::istringstream input{"1 + 2 ="};
    std::ostringstream output{};
    interaction(input,output);
    ASSERT_EQUAL("Result: 3\n",output.str());
}
void testSimpleSubtraction(){
    std::istringstream input{"1 - 2 ="};
    std::ostringstream output{};
    interaction(input,output);
    ASSERT_EQUAL("Result: -1\n",output.str());
}
void testSimpleMultiplication(){
    std::istringstream input{"2 * 3 ="};
    std::ostringstream output{};
    interaction(input,output);
    ASSERT_EQUAL("Result: 6\n",output.str());
}
void testSimpleDivision(){
    std::istringstream input{"6 / 2 ="};
    std::ostringstream output{};
    interaction(input,output);
    ASSERT_EQUAL("Result: 3\n",output.str());
}
void testErrorResync(){
    std::istringstream input{"abc  \n 1 % 2 \n1 + 2\n =\n"};
    std::ostringstream output{};
    interaction(input,output);
    ASSERT_EQUAL("invalid operator, restarting\nResult: 3\n",output.str());
}
void testMultipleOperationsAndResults(){
    std::istringstream input{"1 + 1 + 1 + 2 * 10 -8 =  \n 1 / 2 + \n1 + 2\n =\n"};
    std::ostringstream output{};
    interaction(input,output);
    ASSERT_EQUAL("Result: 42\nResult: 3.5\n",output.str());
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(Adding1plus1Istwo));
	s.push_back(CUTE(Subtracting4From6Is2));
	s.push_back(CUTE(Multiply2By3Is6));
	s.push_back(CUTE(Divide6By3Is2));
	s.push_back(CUTE(testSimpleAddition));
	s.push_back(CUTE(testReadNumber));
	s.push_back(CUTE(testReadNumberEmptyFails));
	s.push_back(CUTE(testReadNumberWithNonNumber));
	s.push_back(CUTE(testReadOperationEmptyFails));
	s.push_back(CUTE(testReadOperationInvalidSymbolFails));
	s.push_back(CUTE(testReadOperationResult));
	s.push_back(CUTE(testReadOperationAll));
	s.push_back(CUTE(testSkipToNewline));
	s.push_back(CUTE(testSkipToNewlineEmpty));
	s.push_back(CUTE(testSimpleSubtraction));
	s.push_back(CUTE(testSimpleMultiplication));
	s.push_back(CUTE(testSimpleDivision));
	s.push_back(CUTE(testSkipToNewlineAsManipulator));
	s.push_back(CUTE(testErrorResync));
	s.push_back(CUTE(testMultipleOperationsAndResults));
	s.push_back(CUTE(DivideByZEroDeliversNullOpt));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
