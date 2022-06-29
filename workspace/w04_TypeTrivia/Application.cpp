#include "Trivia.h"
#include "QuestionGenerator.h"
#include <iostream>




int main() {
	auto questions = createQuestions();
	trivia(std::cout, std::cin, questions);
//	printAll(std::cout, questions);
}

