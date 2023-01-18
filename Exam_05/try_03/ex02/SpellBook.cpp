#include "SpellBook.hpp"

SpellBook::SpellBook(void)
{
}

SpellBook::~SpellBook(void)
{
	std::vector<ASpell *>::iterator ite = spells.end();
	for (std::vector<ASpell *>::iterator it = spells.begin(); it != ite; it++)
		delete *it;
}

void SpellBook::learnSpell(ASpell *spell)
{
	std::vector<ASpell *>::iterator ite = spells.end();
	for (std::vector<ASpell *>::iterator it = spells.begin(); it != ite; it++)
	{
		if ((*it)->getName() == spell->getName())
			return;
	}
	spells.push_back(spell->clone());
}

void SpellBook::forgetSpell(std::string const &spell)
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

ASpell* SpellBook::createSpell(std::string const &spell)
{
	std::vector<ASpell *>::iterator ite = spells.end();
	for (std::vector<ASpell *>::iterator it = spells.begin(); it != ite; it++)
	{
		if ((*it)->getName() == spell)
		{
			return (*it);
		}
	}
	return NULL;
}
