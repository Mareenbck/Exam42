#include "ATarget.hpp"

ATarget::ATarget(std::string type) : type(type)
{
	// std::cout << this->name << ": This looks like another boring day." << std::endl;
}

ATarget::~ATarget(void)
{
	// std::cout << this->name << ": My job here is done!" << std::endl;
}

ATarget::ATarget(void)
{
}

ATarget::ATarget(ATarget const &src)
{
	*this = src;
}

ATarget &ATarget::operator=(ATarget const &rhs)
{
	this->type = rhs.type;
	return *this;
}

std::string const &ATarget::getType(void) const
{
	return this->type;
}

void ATarget::getHitBySpell(ASpell const &spell)
{
	std::cout << this->type << " has been " << spell.getEffects() << "!" << std::endl;
}
