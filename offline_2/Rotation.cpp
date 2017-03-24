#include "stdafx.h"
#include "Rotation.h"


Rotation::Rotation(void)
{
	this->angle = 0.0;
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}

Rotation::Rotation(double angle, double x, double y, double z)
{
	this->angle = angle;
	this->x = x;
	this->y = y;
	this->z = z;
}

Rotation::~Rotation(void)
{
}
