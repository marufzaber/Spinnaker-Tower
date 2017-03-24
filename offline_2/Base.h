#pragma once

#include "Headers.h"

class Base
{
public:

	double cameraHeight;
	double cameraAngle;
	int drawgrid;
	int drawaxes;
	double angle;
	int set;
	GLuint texid,upside1,upside2,upside3,upside4,upsideR1,upsideR2,upsideR3,upsideR4;
	GLuint midside;
	GLuint brickwall;
	GLuint concrete;
	GLuint door;

	bitmapLoader bitmap;

	GLUquadric* IQuadric;

	struct point
	{
		double x,y,z;
	};

	float X[21];
	float Y[21];
	float arr[16];
	float A1[21];
	float B1[21];

	float A2[21];
	float B2[21];

	int count;

	void drawsphere(float radius,int slices,int stacks);
	void drawFilledCircle(float x, float y, float radius);
	void dr();
	void drawHorizontalGrill();
	void drawFilledCirclewithSide();
	void drawSurface();
	void drawSide(int rev);
	void drawGrill();
	void drawFilledCircleWithAngle(float x, float y, float radius,float angles, int a);
	void lower();
	void drawLowerSide();
	void drawMidSurface();
	void drawMidSurfaceU();
	void drawAcrStair();
	void drawStrainghtStair();
	void drawMidSide();
	void drawArcTorus();
	void drawCurveRod();
	void drawMidGril();
	void drawBase();
	void base();
	void initialize();
	Base(void);
	~Base(void);
};

