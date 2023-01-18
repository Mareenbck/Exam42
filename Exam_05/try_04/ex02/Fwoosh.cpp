#include "Fwoosh.hpp"

Fwoosh::Fwoosh(void)
{
	this->name = "Fwoosh";
	this->effects = "fwooshed";
}

Fwoosh::~Fwoosh(void)
{
}

ASpell *Fwoosh::clone(void) const
{
	return(new Fwoosh());
}
