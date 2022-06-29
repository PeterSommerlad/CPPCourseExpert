#include <iostream>
#include <string>

template<typename First, typename...Types>
void printAll(First const & first, Types const &...rest) {
	std::cout << first;
	if constexpr (sizeof...(Types)) {
		std::cout << ", ";
		printAll(rest...);
	}
}


int main(int argc, char **argv) {
	int i { 42 };
	double d { 1.25 };
	std::string book { "Lucid C++" };
	printAll(i, d, book);
}

