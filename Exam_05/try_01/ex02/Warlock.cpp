#include "Warlock.hpp"

Warlock::Warlock(std::string name, std::string title) : name(name), title(title)
{
	std::cout << this->name << ": This looks like another boring day." << std::endl;
	// this->book = new SpellBook();
}

Warlock::~Warlock(void)
{
	std::cout << this->name << ": My job here is done!" << std::endl;
	// delete book;
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

void Warlock::introduce() const
{
	std::cout << this->name << ": I am " << this->name << ", " << this->title << "!" << std::endl;
}

void Warlock::learnSpell(ASpell *spell)
{
	this->book.learnSpell(spell);
}

void Warlock::forgetSpell(std::string const &spell)
{
	this->book.forgetSpell(spell);
}

void Warlock::launchSpell(std::string const &spell, ATarget const &target)
{
	ASpell *spelli = this->book.createSpell(spell);
	spelli->launch(target);
}
