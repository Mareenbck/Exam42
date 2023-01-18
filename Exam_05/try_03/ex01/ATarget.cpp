#include "ATarget.hpp"

ATarget::ATarget(void)
{
}

ATarget::ATarget(ATarget const &src)
{
	*this = src;
}

ATarget::ATarget(std::string type) : type(type)
{
}

ATarget::~ATarget(void)
{
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

void ATarget::getHitBySpell(ASpell const &spell) const
{
	std::cout << this->type << " has been "<< spell.getEffects() << "!" << std::endl;
}
