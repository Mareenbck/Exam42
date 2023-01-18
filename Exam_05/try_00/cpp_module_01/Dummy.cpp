#include "Fwoosh.hpp"

Dummy::~Dummy(void)
{
	// std::cout << this->name << ": My job here is done!" << std::endl;
}

Dummy::Dummy(void)
{
	this->type = "Target Practice Dummy";
}

// Dummy::Dummy(Dummy const &src)
// {
// 	*this = src;
// }

// Dummy &Dummy::operator=(Dummy const &rhs)
// {
// 	this->type = rhs.type;
// 	return *this;
// }

// std::string const &Dummy::getType(void) const
// {
// 	return this->type;
// }

ATarget *Dummy::clone(void)
{
	return (new Dummy());
}
