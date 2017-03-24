#pragma once

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "megastructure.h"

#include<GL/glut.h>
#include "Transform.h"

class MainPillar
{
public:

	struct point
	{
		double x,y,z;
	};

	Transform *transform;
	
	double radius, inclination;

	void initialize();

	void draw();
	void draw_pillar(double height, double radius);
	void draw_top(double height, double radius);
	void draw_bridge(double l, double b, double h);
	void draw_inner_pillar(double height, double radius);

	MainPillar(void);
	~MainPillar(void);

};

