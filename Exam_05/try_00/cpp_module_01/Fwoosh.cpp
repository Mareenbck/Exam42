#include "Fwoosh.hpp"

Fwoosh::~Fwoosh(void)
{
	// std::cout << this->name << ": My job here is done!" << std::endl;
}

Fwoosh::Fwoosh(void)
{
	this->name = "Fwoosh";
	this->effects = "fwooshed";
}

// Fwoosh::Fwoosh(Fwoosh const &src)
// {
// 	*this = src;
// }

// Fwoosh &Fwoosh::operator=(Fwoosh const &rhs)
// {
// 	this->name = rhs.name;
// 	this->effects = rhs.effects;
// 	return *this;
// }

// std::string const &Fwoosh::getName(void) const
// {
// 	return this->name;
// }

// std::string const &Fwoosh::getEffects(void) const
// {
// 	return this->effects;
// }

ASpell *Fwoosh::clone(void)
{
	return (new Fwoosh());
}
