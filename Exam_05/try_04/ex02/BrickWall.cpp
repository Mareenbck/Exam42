#include "BrickWall.hpp"

BrickWall::BrickWall(void)
{
	this->type = "Inconspicuous Red-brick Wall";
}

BrickWall::~BrickWall(void)
{
}

ATarget *BrickWall::clone(void) const
{
	return(new BrickWall());
}
