#include "Polymorph.hpp"

Polymorph::Polymorph(void)
{
	this->name = "Polymorph";
	this->effects = "turned into a critter";
}

Polymorph::~Polymorph(void)
{
}

ASpell *Polymorph::clone(void) const
{
	return (new Polymorph());
}
