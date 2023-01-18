#ifndef ATARGET_HPP
# define ATARGET_HPP

# include <iostream>

class ASpell;

class ATarget
{
	public:
		ATarget(void);
		ATarget(std::string type);
		ATarget(ATarget const &src);
		virtual ~ATarget(void);

		ATarget &operator=(ATarget const &rhs);

		std::string const &getType(void) const;

		virtual ATarget *clone(void) const = 0;

		void getHitBySpell(ASpell const &spell);

	protected:
		std::string type;
};

#endif
