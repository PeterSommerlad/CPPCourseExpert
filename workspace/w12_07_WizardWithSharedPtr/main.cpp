#include "Wizard.h"
#include <iostream>

int main() {
	Wizard w{"Gandalf"};

	std::cout << w.doMagic("Earthquake");
}
