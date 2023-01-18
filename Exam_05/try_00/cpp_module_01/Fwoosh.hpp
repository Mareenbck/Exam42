#ifndef FWOOSH_HPP
# define FWOOSH_HPP

#include <iostream>
#include "ASpell.hpp"

class Fwoosh : public ASpell
{
	public:
		Fwoosh(void);
		Fwoosh(Fwoosh const &src);
		virtual ~Fwoosh(void);

		Fwoosh &operator=(Fwoosh const &rhs);

		// std::string const &getType(void) const;

		virtual ASpell *clone(void);

};

#endif
