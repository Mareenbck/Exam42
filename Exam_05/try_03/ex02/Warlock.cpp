#include "Warlock.hpp"

Warlock::Warlock(std::string name, std::string title) : name(name), title(title)
{
	std::cout << this->name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock(void)
{
	std::cout << this->name << ": My job here is done!" << std::endl;
}

std::string const &Warlock::getName(void) const
{
	return this->name;
}

std::string const &Warlock::getTitle(void) const
{
	return this->title;
}

void Warlock::setTitle(std::string const &str)
{
	this->title = str;
}

void Warlock::introduce(void) const
{
	std::cout << this->name << ": I am " << this->name << ", "<< this->title << "!" << std::endl;
}

void Warlock::learnSpell(ASpell *spell)
{
	book.learnSpell(spell);
}

void Warlock::forgetSpell(std::string spellName)
{
	book.forgetSpell(spellName);
}

void Warlock::launchSpell(std::string spellName, ATarget const &target)
{
	ASpell *newSpell = book.createSpell(spellName);
	if (newSpell)
		newSpell->launch(target);
}
