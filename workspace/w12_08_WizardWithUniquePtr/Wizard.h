#ifndef WIZARD_H_
#define WIZARD_H_
#include <string>
#include <memory>

class Wizard {
	std::unique_ptr<class WizardImpl> pImpl;
public:
	explicit Wizard(std::string name);
	~Wizard();
	std::string doMagic(std::string wish);
};

#endif /* WIZARD_H_ */
