#include "Question.h"

#include <string>
#include <algorithm>
#include <cctype>

namespace {
bool compareWhitespaceless(std::string const & first, std::string const & second) {
	std::string whitespacelessFirst { first }, whitespacelessSecond { second };
	whitespacelessFirst.erase(std::remove_if(whitespacelessFirst.begin(), whitespacelessFirst.end(), ::isspace), whitespacelessFirst.end());
	whitespacelessSecond.erase(std::remove_if(whitespacelessSecond.begin(), whitespacelessSecond.end(), ::isspace), whitespacelessSecond.end());
	return whitespacelessFirst == whitespacelessSecond;
}
}

bool Question::checkTypeT(std::string const & answer) const {
	return compareWhitespaceless(answer, typeT);
}

bool Question::checkTypeP(std::string const & answer) const {
	return compareWhitespaceless(answer, typeParamType);
}

