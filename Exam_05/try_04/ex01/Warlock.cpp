#include "Warlock.hpp"

Warlock::Warlock(std::string name, std::string title) : name(name), title(title)
{
	std::cout << this->name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock(void)
{
	std::cout << this->name << ": My job here is done!" << std::endl;
	std::vector<ASpell *>::iterator ite = spells.end();
	for (std::vector<ASpell *>::iterator it = spells.begin(); it != ite; it++)
		delete *it;
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
	std::cout << this->name << ": I am "<< this->name << ", "<< this->title << "!" << std::endl;
}

void Warlock::learnSpell(ASpell *spell)
{
	std::vector<ASpell *>::iterator ite = spells.end();
	for (std::vector<ASpell *>::iterator it = spells.begin(); it != ite; it++)
	{
		if ((*it)->getName() == spell->getName())
			return ;
	}
	spells.push_back(spell->clone());
}

void Warlock::forgetSpell(std::string spell)
{
	std::vector<ASpell *>::iterator ite = spells.end();
	for (std::vector<ASpell *>::iterator it = spells.begin(); it != ite; it++)
	{
		if ((*it)->getName() == spell)
		{
			delete *it;
			it = spells.erase(it);
		}
	}
}

void Warlock::launchSpell(std::string spell, ATarget &target)
{
	std::vector<ASpell *>::iterator ite = spells.end();
	for (std::vector<ASpell *>::iterator it = spells.begin(); it != ite; it++)
	{
		if ((*it)->getName() == spell)
		{
			(*it)->launch(target);
		}
	}
}
