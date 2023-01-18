#ifndef ASPELL_HPP
# define ASPELL_HPP

# include <iostream>

class ATarget;

class ASpell
{
	public:
		ASpell(void);
		ASpell(std::string name, std::string effects);
		ASpell(ASpell const &src);
		virtual ~ASpell(void);

		ASpell &operator=(ASpell const &rhs);

		std::string const &getName(void) const;
		std::string const &getEffects(void) const;

		virtual ASpell *clone(void) const = 0;

		void launch(ATarget const &target);

	protected:
		std::string name;
		std::string effects;
};

#endif
