#ifndef DUMMY_HPP
# define DUMMY_HPP

#include <iostream>
#include "ATarget.hpp"

class Dummy : public ATarget
{
	public:
		Dummy(void);
		Dummy(Dummy const &src);
		virtual ~Dummy(void);

		Dummy &operator=(Dummy const &rhs);

		// std::string const &getType(void) const;

		virtual ATarget *clone(void);

};

#endif
