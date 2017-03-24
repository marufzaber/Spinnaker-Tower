#pragma once
#include "Rotation.h"
#include "Position.h"
class Transform
{
public:

	Rotation *rotation;
	Position *position;

	Transform(void);
	~Transform(void);

	void set_position(double x, double y, double z);
	void set_rotaion(double angle, double x, double y, double z);
};

