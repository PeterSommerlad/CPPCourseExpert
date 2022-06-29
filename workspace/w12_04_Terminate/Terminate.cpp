#include <iostream>

struct Ball {
};

void barrater() noexcept {
	throw Ball{};
}

int main() {
	try {
		barrater();
	} catch(Ball const & b) {
		std::cout << "caught the ball!";
	}
}
