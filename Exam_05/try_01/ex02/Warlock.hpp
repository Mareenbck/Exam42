#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# include <vector>
# include "ASpell.hpp"
# include "SpellBook.hpp"


class Warlock
{
	private:
		std::string name;
		std::string title;
		SpellBook book;
		// std::vector<ASpell *> vect;

		Warlock(void);
		Warlock(const Warlock &src);
		Warlock &operator=(const Warlock &rhs);

	public:
		Warlock(std::string name, std::string title);
		~Warlock(void);

		std::string const &getName(void) const;
		std::string const &getTitle(void) const;
		void setTitle(std::string const &str);

		void introduce() const;
		void learnSpell(ASpell *spell);
		void forgetSpell(std::string const &spell);
		void launchSpell(std::string const &spell, ATarget const &target);
};

#endif
