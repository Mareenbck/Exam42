#ifndef SPELLBOOK_HPP
# define SPELLBOOK_HPP

# include <iostream>
# include <vector>
# include "ASpell.hpp"

class ASpell;

class SpellBook
{
	private:
		SpellBook(const SpellBook &src);
		SpellBook &operator=(const SpellBook &rhs);

		std::vector<ASpell *> book;

	public:
		SpellBook(void);
		~SpellBook(void);

		void learnSpell(ASpell *spell);
		void forgetSpell(std::string const &spell);
		ASpell* createSpell(std::string const &spell);
};

#endif
