#ifndef TRIVIA_H_
#define TRIVIA_H_

#include "Question.h"
#include <iosfwd>
#include <vector>

constexpr size_t const NUMBER_OF_QUESTIONS_TO_ASK = 10;

void printAll(std::ostream& out, std::vector<Question> const & questions);
std::vector<size_t> createRandomIndices(size_t to_exclusive);
std::vector<Question> pickQuestionsToAsk(std::vector<Question> const & questions);
void printAwesomeness(std::ostream& out, unsigned correctAnswers, unsigned numberOfQuestions);
void trivia(std::ostream& out, std::istream& in, std::vector<Question> const & questions);


#endif /* TRIVIA_H_ */
