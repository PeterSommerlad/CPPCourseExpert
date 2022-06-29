#include "Wizard.h"
#include "WizardIngredients.h"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string>

class WizardImpl { // all magic details public
	std::string name;
	MagicWand wand;
	std::vector<Spell> books;
	std::vector<Potion> potions;
	std::string searchForSpell(std::string const &wish);
	Potion mixPotion(std::string const &recipe);
	void castSpell(Spell spell);
	void applyPotion(Potion phial);
public:
	explicit WizardImpl(std::string name = "Rincewind") :
			name { name }, wand { } {
	}
	std::string doMagic(std::string const &wish);
	void learnSpell(std::string const &newspell);
	void mixAndStorePotion(std::string const &potion);
	std::string getName() const {
		return name;
	}
};

std::string WizardImpl::searchForSpell(std::string const &wish) {
	auto const spell = find(begin(books), end(books), wish);
	return spell != end(books) ? *spell : "";
}

Potion WizardImpl::mixPotion(std::string const &recipe) {
	auto const potion = find(begin(potions), end(potions), recipe);
	return potion != end(potions) ? *potion : "";
}

void WizardImpl::castSpell(std::string spell) {
}

void WizardImpl::applyPotion(Potion phial) {
}

std::string WizardImpl::doMagic(std::string const &wish) {
	auto spell = searchForSpell(wish);
	if (!spell.empty()) {
		castSpell(spell);
		return "wootsh";
	}
	auto potion = mixPotion(wish);
	if (!potion.empty()) {
		applyPotion(potion);
		return "zapp";
	}
	throw std::logic_error { "magic failed" };
}

void WizardImpl::learnSpell(const std::string& newspell) {
	this->books.push_back(newspell);
}

void WizardImpl::mixAndStorePotion(const std::string& potion) {
	this->potions.push_back(potion);
}

//-- Wizard

Wizard::Wizard(std::string name) :
		pImpl { std::make_shared<WizardImpl>(name) } {
}

std::string Wizard::doMagic(std::string wish) {
	return pImpl->doMagic(wish);
}

