#pragma once

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include "bitmapLoader.h"
#include "RoundBows.h"
#include "MainPillar.h"


#include<GL/glut.h>

#define BASE_HEIGHT 803
#define BASE_WIDTH 803
#define pi 3.14159265359


class megastructure
{

public:

	/*MainPillar *pillar;
	RoundBows *round_bows;*/

	GLuint glass_tex_id;

	GLuint base_texture_id;
	bitmapLoader bitmapLoader;
	GLUquadric *quadric;

	struct point
	{
		double x,y,z;
	};

	float base_height;
	float base_width;

	megastructure(void);
	~megastructure(void);

	void initBitmaps();
	void initTextureSize();
	void draw();
	void draw_base();
	void draw_pillers();
	void set_glass_tex(GLuint tex_id);

private:

	
};

