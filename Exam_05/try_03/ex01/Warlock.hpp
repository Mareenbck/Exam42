#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# include <vector>
# include "ASpell.hpp"

class Warlock
{
	private:
		std::string name;
		std::string title;
		std::vector<ASpell *> spells;

		Warlock(void);
		Warlock(Warlock const &src);
		Warlock &operator=(Warlock const &rhs);

	public:
		Warlock(std::string name, std::string title);
		~Warlock(void);

		std::string const &getName(void) const;
		std::string const &getTitle(void) const;
		void setTitle(std::string const &str);

		void introduce(void) const;
		void learnSpell(ASpell *spell);
		void forgetSpell(std::string spellName);
		void launchSpell(std::string spellName, ATarget const &target);

};

#endif
