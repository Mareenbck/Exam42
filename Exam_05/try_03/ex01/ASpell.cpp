#include "ASpell.hpp"

ASpell::ASpell(void)
{
}

ASpell::ASpell(ASpell const &src)
{
	*this = src;
}

ASpell::ASpell(std::string name, std::string effects) : name(name), effects(effects)
{
}

ASpell::~ASpell(void)
{
}

ASpell &ASpell::operator=(ASpell const &rhs)
{
	this->name = rhs.name;
	this->effects = rhs.effects;
	return *this;
}

std::string const &ASpell::getName(void) const
{
	return this->name;
}

std::string const &ASpell::getEffects(void) const
{
	return this->effects;
}

void ASpell::launch(ATarget const &target) const
{
	target.getHitBySpell(*this);
}
