#include "SpellBook.hpp"

SpellBook::SpellBook(void)
{
}

SpellBook::~SpellBook(void)
{
	std::vector<ASpell *>::iterator ite = book.end();
	for (std::vector<ASpell *>::iterator it = book.begin(); it != ite; it++)
		delete *it;
	this->book.clear();
}

void SpellBook::learnSpell(ASpell *spell)
{
	std::vector<ASpell *>::iterator ite = book.end();
	for (std::vector<ASpell *>::iterator it = book.begin(); it != ite; it++)
	{
		if ((*it)->getName() == spell->getName())
			return ;
	}
	book.push_back(spell->clone());
}

void SpellBook::forgetSpell(std::string const &spell)
{
	std::vector<ASpell *>::iterator ite = this->book.end();

	for (std::vector<ASpell *>::iterator it = this->book.begin(); it != ite; it++)
	{
		if ((*it)->getName() == spell)
		{
			delete *it;
			it = this->book.erase(it);
		}
	}
}

ASpell* SpellBook::createSpell(std::string const &spell)
{
	std::vector<ASpell *>::iterator ite = this->book.end();

	for (std::vector<ASpell *>::iterator it = this->book.begin(); it != ite; it++)
	{
		if ((*it)->getName() == spell)
		{
			return ((*it));
		}
	}
	return (NULL);
}
