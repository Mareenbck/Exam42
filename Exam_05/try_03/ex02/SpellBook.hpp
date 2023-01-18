#ifndef SPELLBOOK_HPP
# define SPELLBOOK_HPP

# include <iostream>
# include <vector>
# include "ASpell.hpp"

class SpellBook
{
	private:
		std::vector<ASpell *> spells;

		SpellBook(SpellBook const &src);
		SpellBook &operator=(SpellBook const &rhs);

	public:
		SpellBook(void);
		~SpellBook(void);

		void learnSpell(ASpell *spell);
		void forgetSpell(std::string const &spell);
		ASpell* createSpell(std::string const &spell);

};

#endif
