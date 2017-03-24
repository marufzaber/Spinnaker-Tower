#include "stdafx.h"
#include "Transform.h"


Transform::Transform(void)
{
	position = new Position();
	rotation = new Rotation();
}


Transform::~Transform(void)
{
}

void Transform::set_position(double x, double y, double z)
{
	position->x = x;
	position->y = y;
	position->z = z;
}

void Transform::set_rotaion(double angle, double x, double y, double z)
{
	rotation->angle = angle;
	rotation->x = x;
	rotation->y = y;
	rotation->z = z;


}