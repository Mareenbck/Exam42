#include "Fireball.hpp"

Fireball::Fireball(void)
{
	this->name = "Fireball";
	this->effects = "burnt to a crisp";
}

Fireball::~Fireball(void)
{
}

ASpell *Fireball::clone(void) const
{
	return(new Fireball());
}
