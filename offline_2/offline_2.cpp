/*************************************************************************
// offline_2.cpp : Defines the entry point for the console application.
// this code is done in visual studio ultimate 2012
// the "stdafx.h" is included in addition to the given source code

	student id: 0905019
****************************************************************************/

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "megastructure.h"
#include "Base.h"
#include "Vectors.h"
#include "Cameras.h"
#include "bitmapLoader.h"

#include<GL/glut.h>

//#define pi 2*acos(0)
#define pi 3.14159265359

Vectors origin(0, 0, 0);
Vectors I(1, 0, 0);
Vectors J(0, 1, 0);
Vectors K(0, 0, 1);

Cameras camera(I,J,K);

//make a global variable -- for tracking the anglular position of camera
double cameraAngle;			//in radian
double cameraAngleDelta;

double cameraHeight;
double cameraRadius;

double rectAngle;	//in degree

int drawgrid;
int drawaxes;
double angle;
bool isFirst = true;
int rotationAngle = 0;

//parameters for bouncing ball
double ballHeight = 70;
double ballVelocity = 0;
double ballRadius = 15;
const double G = -0.0098;

//parameters for cuboid
double cubeSide = 20;
double cubeRadius = 5;
const double MaxCubeSide = 20;
const double MaxCubeRadius = 20;

const int CUBE = 0;
const int SPINDLE = 1;
const int BALL = 2;

//robot arm
double rotation_1 = 0;
double rotation_2 = 0;
double rotation_3 = 0;

int drawingMode = CUBE;

double light_angle = 0;
double light_color = 1;

bitmapLoader bitmaploader;
GLUquadric* IQuadric;
GLuint sky1;
GLuint glass_sky;
//add the following lines at initialization function



megastructure *mega;
Base *base;

struct point
{
	double x,y,z;
};


void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);
			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);
			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}


void drawSquare(double a, double h)
{
	glBegin(GL_QUADS);{
		glVertex3f( a, a,0);
		glVertex3f( a,-a,0);
		glVertex3f(-a,-a,0);
		glVertex3f(-a, a,0);
	}glEnd();
}

void drawCuboidSurfaces(double a, double r){

	glPushMatrix();{

		glTranslatef(0, 0, a);
		glRotatef(0,0,0,1);
		drawSquare(a - r, r);

	}glPopMatrix();

	glPushMatrix();{

		glTranslatef(0, 0, -a);
		glRotatef(0,0,0,1);
		drawSquare(a - r, r);

	}glPopMatrix();

	glPushMatrix();{

		glTranslatef(0, a, 0);
		glRotatef(90,1,0,0);
		drawSquare(a - r, r);

	}glPopMatrix();

	glPushMatrix();{

		glTranslatef(0, -a, 0);
		glRotatef(90,1,0,0);
		drawSquare(a - r, r);

	}glPopMatrix();

	glPushMatrix();{

		glTranslatef(a, 0, 0);
		glRotatef(90,0,1,0);
		drawSquare(a - r, r);

	}glPopMatrix();

	glPushMatrix();{

		glTranslatef(-a, 0, 0);
		glRotatef(90,0,1,0);
		drawSquare(a - r, r);

	}glPopMatrix();
}

void drawQuarterCylinder(double height, double radius){

	const int MAX = 50;
	struct point points[MAX][MAX];
	int i,j;
	int stacks = 30;
	int slices = 10;
	double h,r;
	for(i=0;i<=stacks;i++)
	{
		h = height * cos(((double)i/(double)stacks)*(pi));
		r = radius;
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*pi/2);
			points[i][j].y=r*sin(((double)j/(double)slices)*pi/2);
			points[i][j].z=h;
		}
		
	}

	for(i=0;i<stacks;i++)
	{
		for(j=0;j<slices;j++)
		{
			glColor3f(1,0,0);
			glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
				
			}glEnd();
		}
		
	}
}

void drawCuboidCylinders(double a, double r){

	double h = a -r;
	int i;
	int ROT_X[] = {1, -1, -1, 1};
	int ROT_Y[] = {1, 1, -1, -1};
	double ROT_Z[] = {0, 90, 180, 270};
	
	//rotating about z axis
	for(i=0;i<4;i++){
	
		glPushMatrix();{
			glTranslatef(h*ROT_X[i], h*ROT_Y[i], 0);
			glRotatef(ROT_Z[i],0,0,1);

			drawQuarterCylinder(h, r);
		}glPopMatrix();
	}
	
	//rotating about y axis
	for(i=0;i<4;i++){
		glPushMatrix();{
			glTranslatef( 0, h*ROT_X[i], -h*ROT_Y[i]);
			glRotatef(-ROT_Z[i],1,0,0);

			glRotatef(90, 0,1,0);
			drawQuarterCylinder(h, r);
		}glPopMatrix();
	}

	//rotating about x axis
	for(i=0;i<4;i++){
		glPushMatrix();{
			glTranslatef( h*ROT_X[i], 0, h*ROT_Y[i]);
			glRotatef(-ROT_Z[i],0,1,0);

			glRotatef(90, 1,0,0);
			drawQuarterCylinder(h, r);
		}glPopMatrix();
	}

}

void drawEighthSphere(double radius){

	const int MAX = 50;
	struct point points[MAX][MAX];
	int i,j;
	int stacks = 30;
	int slices = 10;
	double h,r;
	for(i=0;i<=stacks;i++)
	{
		h = radius * cos(((double)i/(double)stacks)*(pi/2));
		r = sqrt(radius*radius-h*h);
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*pi/2);
			points[i][j].y=r*sin(((double)j/(double)slices)*pi/2);
			points[i][j].z=h;
		}		
	}

	for(i=0;i<stacks;i++)
	{
		for(j=0;j<slices;j++)
		{
			glColor3f(0,0,1);
			glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
				
			}glEnd();
		}
		
	}
}

void drawCuboidSpheres(double a, double r){

	int ROT[] = {0,90,180,270};
	int TRANS_X[] = {1,-1,-1,1};
	int TRANS_Y[] = {1,1,-1,-1};
	int i;

	int c = a-r;

	//top four spheres at corners
	for(i=0;i<4;i++){
		glPushMatrix();{
			glTranslatef(c*TRANS_X[i],c*TRANS_Y[i],c);
			glRotatef(ROT[i],0,0,1);
			drawEighthSphere(r);
		}glPopMatrix();
	}

	//bottom four spheres at corners
	for(i=0;i<4;i++){
		glPushMatrix();{
			glTranslatef(c*TRANS_X[i],c*TRANS_Y[i], -c);
			glRotatef(ROT[i],0,0,1);

			glRotatef(90,0,1,0);
			drawEighthSphere(r);
		}glPopMatrix();
	}
}

void drawCuboid(double side, double radius){

	double a = side;
	double r = radius;
	
	glColor3f(1, 1, 1);
	drawCuboidSurfaces(a,r);
	drawCuboidCylinders(a,r);
	drawCuboidSpheres(a,r);

	
}

void changeCubeSide(double mode){

	//if(cubeSide >= 0 && cubeSide <= MaxCubeSide )cubeSide+=mode/2;
	if(cubeRadius >= 0 && cubeRadius <= MaxCubeRadius)cubeRadius-=mode/2;

	/*if(cubeSide < 0)cubeSide = 0;
	if(cubeSide > MaxCubeSide)cubeSide = MaxCubeSide;*/

	if(cubeRadius < 0)cubeRadius = 0;
	if(cubeRadius > MaxCubeRadius)cubeRadius = MaxCubeRadius;
}

void drawss()
{
	glPushMatrix();{
		glRotatef(angle,0,0,1);
		glTranslatef(75,0,0);
		glRotatef(2*angle,0,0,1);

				
		glPushMatrix();{
			glRotatef(angle,0,0,1);
			glTranslatef(25,0,0);
			glRotatef(3*angle,0,0,1);
			glColor3f(0.0, 0.0, 1.0);
			drawSquare(5,2);

		}glPopMatrix();

	

		glColor3f(1.0, 0.0, 0.0);
		drawSquare(10.0,2);
	}glPopMatrix();

}

//draws half sphere
void drawsphere(float radius,int slices,int stacks)
{
	
	const int MAX = 200;
	struct point points[MAX][MAX];
	int i,j;
	double h,r;
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2)) + ballHeight;	
		r=sqrt(radius*radius-h*h);
		if(isFirst)printf("height: %lf, radius: %lf\n",h,r);
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
		
	}

	isFirst = false;
	for(i=0;i<stacks;i++)
	{
		for(j=0;j<slices;j++)
		{
			glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
			glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
				
			}glEnd();
		}
		
	}
}

double gaussian(double x, double height){
	double dev = 18.0;
	double result = 0;
	result = -1*(x*x/(2*dev*dev));
	result = height*exp(result);
	return result;
}
void drawObjects(int stack, int slice){

	const int MAX = 200;
	struct point points[MAX][MAX];
	int i,j;

	int st = 150;
	int sl = 100;
	int maxHeight = 50;
	int maxRadius = 20;

	for(i=0;i<=st;i++){
		double h,r;
		h = maxHeight * cos(((double)i/(double)st)*(pi));
		//r=sqrt(maxHeight*maxHeight-h*h);
		r = gaussian(h,maxRadius);
		//if(isFirst)printf("height: %lf radius: %lf\n",h,r);

		for(j=0;j<=sl;j++)
		{
			points[i][j].x=r*cos(((double)(j)/(double)(sl))*2*pi
				- (double(i)/double(st))*5
				+ double((rotationAngle%360))/360*2*pi
				);
			points[i][j].y=r*sin(((double)(j)/(double)(sl))*2*pi
				- (double(i)/double(st))*5
				+ double((rotationAngle%360))/360*2*pi
				);
			points[i][j].z=h;
		}
	}

	const int GREEN = 0;
	const int RED = 1;

	int stripeWidth = sl/20;
	int stripeCount = 0;
	int stipeColor = GREEN;

	isFirst = false;
	for(i=0;i<st;i++)
	{
		for(j=0;j<sl;j++)
		{
			//glColor3f((double)j/(double)sl,(double)j/(double)sl,(double)j/(double)sl);
			if(stipeColor == GREEN){
				glColor3f(0,1,0);				
			}
			else if(stipeColor == RED){
				glColor3f(1,0,0);
			}
			stripeCount++;
			if(stripeCount == stripeWidth){
				stipeColor = (stipeColor + 1)%2;
				stripeCount = 0;
			}
			glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
				
			}glEnd();
		}
	}
}

void rotateObject(int mode){
	rotationAngle += mode*2;
}

void drawBouncingBall(){
	
	const int MAX = 200;
	struct point points[MAX][MAX];
	int i,j;

	int st = 150;
	int sl = 100;
	int maxRadius = ballRadius;

	for(i=0;i<=st;i++){
		double h,r;
		h = maxRadius * cos(((double)i/(double)st)*(pi));
		r=sqrt(maxRadius*maxRadius-h*h);
		//r = gaussian(h,maxRadius);
		//if(isFirst)printf("height: %lf radius: %lf\n",h,r);

		for(j=0;j<=sl;j++)
		{
			points[i][j].x=r*cos(((double)(j)/(double)(sl))*2*pi);
			points[i][j].y=r*sin(((double)(j)/(double)(sl))*2*pi);
			points[i][j].z=h + ballHeight;
		}
	}

	const int GREEN = 0;
	const int RED = 1;

	int stripeWidth = sl/20;
	int stripeHeight = st/20;
	int stripeWidthCount = 0;
	int stripeHeightCount = 0;
	int stipeColor = GREEN;

	isFirst = false;
	for(i=0;i<st;i++)
	{
		for(j=0;j<sl;j++)
		{
			//glColor3f((double)j/(double)sl,(double)j/(double)sl,(double)j/(double)sl);
			if(stipeColor == GREEN){
				glColor3f(0,1,0);				
			}
			else if(stipeColor == RED){
				glColor3f(1,0,0);
			}
			stripeWidthCount++;
			if(stripeWidthCount == stripeWidth){
				stipeColor = (stipeColor + 1)%2;
				stripeWidthCount = 0;
			}
			glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
				
			}glEnd();
		}
		stripeHeightCount++;
		if(stripeHeightCount == stripeHeight){
			stipeColor = (stipeColor + 1)%2;
			stripeHeightCount = 0;
		}
	}
}

void updateVelocity(){
	if(ballHeight - ballRadius <= 0){
		ballVelocity = -1*ballVelocity;
	}
	ballHeight += ballVelocity;
	ballVelocity += G;
}

void drawCylinder(){

	const int MAX = 50;
	struct point points[MAX][MAX];
	int i,j;
	int stacks = 30;
	int slices = 10;
	double height = 40;
	double radius = 10;
	double h,r;
	for(i=0;i<=stacks;i++)
	{
		h = height * cos(((double)i/(double)stacks)*(pi/2));
		r = radius;
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
		
	}

	for(i=0;i<stacks;i++)
	{
		for(j=0;j<slices;j++)
		{
			//glColor3f(1,0,0);
			glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
				
			}glEnd();
		}
		
	}
}

void drawRobotArm(){

	glPushMatrix();{
		glColor3f(1,0,0);
		glRotatef(rotation_2,1,0,0);		
		glRotatef(rotation_1,0,1,0);
		glTranslatef(0,0,-40);
		drawCylinder();

		glPushMatrix();{

			glColor3f(0,1,0);
			glRotatef(rotation_3,1,0,0);
			glTranslatef(0,0,-40);
			drawCylinder();

		}glPopMatrix();
	}glPopMatrix();
}

void rotate_2(double mode){
	
	if(rotation_2 >= -45 && rotation_2 <= 45)rotation_2 += mode;
	if(rotation_2 > 45)rotation_2 = 45;
	if(rotation_2 < -45)rotation_2 = -45;
}

void rotate_1(double mode){
	
	if(rotation_1 >= 0 && rotation_1 <= 90)rotation_1 += mode;
	if(rotation_1 < 0)rotation_1 = 0;
	if(rotation_1 > 90)rotation_1 = 90;
}

void rotate_3(double mode){
	
	if(rotation_3 >= 0 && rotation_3 <= 90)rotation_3 += mode;
	if(rotation_3 < 0)rotation_3 = 0;
	if(rotation_3 > 90)rotation_3 = 90;

}


void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':	//reverse the rotation of camera
            camera.Turn(2);
			break;

		case '2':	//increase rotation of camera by 10%
            camera.Turn(-2);
			break;

		case '3':	//decrease rotation
            camera.Pitch(-2);
			break;

		case '4':	//decrease rotation
            camera.Pitch(2);
			break;
        case '5':	//decrease rotation
			camera.Roll(2);
			break;
        case '6':	//decrease rotation
			camera.Roll(-2);
			break;
        case '7':	//decrease rotation
            drawgrid=1-drawgrid;
			break;

		case 'l':
			if(light_color > 0)light_color -= 0.1;
			if(light_color <= 0)light_color = 0;
			break;
		case 'k':
			if(light_color < 1)light_color += 0.1;
			if(light_color >= 1)light_color = 1;
			break;
			
		case 'o':
			light_angle += 2*pi/180;
			if(light_angle > 360*pi/180)light_angle = 0;
			break;

		case 'p':
			light_angle -= 2*pi/180;
			if(light_angle < -(360*pi/180))light_angle = 0;
			break;
			
		case 'n':

			break;

		case 'm':

			break;
		default:
			break;

	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
            camera.Move(camera.front,-2);
			break;
		case GLUT_KEY_UP:		// up arrow key
            camera.Move(camera.front,2);
			break;

		case GLUT_KEY_RIGHT:
            camera.Move(camera.right,2);
			break;
		case GLUT_KEY_LEFT:
            camera.Move(camera.right,-2);
			break;

		case GLUT_KEY_PAGE_UP:
            camera.Move(camera.up,2);
			break;
		case GLUT_KEY_PAGE_DOWN:
            camera.Move(camera.up,-2);
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:

			break;
		case GLUT_KEY_END:

			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;	
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}

void draw_skybox()
{
	glPushMatrix();{
    //glScalef(5,5,5);

    double coef[4];

	coef[0] = 0;	//-1.x
	coef[1] = 0;	//0.y
	coef[2] = 1;	//0.z
	coef[3] = 0;	//10

    //glClipPlane(GL_CLIP_PLANE0,coef);
	//glEnable(GL_CLIP_PLANE0);{

        glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, sky1);
            gluQuadricNormals(IQuadric,GLU_SMOOTH);
            gluQuadricTexture(IQuadric, GLU_TRUE);
            gluSphere(IQuadric,400,20,20);
        glDisable(GL_TEXTURE_2D);
	//}glDisable(GL_CLIP_PLANE0);
    }glPopMatrix();
}

void lighting()
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);


	double Angle = 30*pi/180;
	
	//local directed diffused light
	
	/*GLfloat diffuseColor[] = {0.5f, 0.50f, 0.50f, 1.0f}; //Color (0.5, 0.2, 0.2)
    GLfloat lightDir[] = {-1.0, 1.0, 1.0, 0.0}; //Coming from the direction (-1, 0.5, 0.5)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightDir);*/
	
	//Add directed light
	
	/*GLfloat lightColor1[] = {1.0f, 1.0f, 1.0f, 1.0f}; 
	GLfloat lightPos1[] = {1.0f, 1.0f, 1.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor1);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);*/
	
	GLfloat amb0[] = {4, 4, 4, 0}; // define some colors
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb0);

	GLfloat spot[] = {0, 4, 0, 1};
    GLfloat spotpos[] = {50, 50, 0, 1};
    GLfloat spotdir[] = {-1,-1, 0, 0};
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30); // a cutoff angle of 45
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, 2);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spot);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,spot);
    glLightfv(GL_LIGHT0,GL_POSITION,spotpos);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION, spotdir);
    glEnable(GL_NORMALIZE); //Automatically normalize normals needed by the illumination model
    
	double light_radius = 100;
	double light_height = 200;
	GLfloat diffusePoint[] = {light_color, light_color, 1, 1.0}; //Color (0.5, 0.5, 0.5)
	GLfloat position[] = {light_radius*cos(light_angle), light_radius*sin(light_angle), light_height, 1.0};
   glLightfv(GL_LIGHT1, GL_DIFFUSE, diffusePoint); //
   glLightfv(GL_LIGHT1, GL_POSITION, position);
   glEnable(GL_LIGHT1);
	/*
	//Add positioned light
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	*/
	
	GLfloat unset[]={0,0,0,1};
	
		
	//object being illuminated
/**/  /* GLfloat mat_ambient[] = { 0.0, 0.0, 1.0, 1.0 };
   GLfloat mat_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
   GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0 }; //equal to the light source
   GLfloat low_shininess[] = { 5.0 };
   GLfloat mid_shininess[] = { 50.0 };
   GLfloat high_shininess[] = { 100.0 };
  
   glPushMatrix();
   glTranslatef (-40, -40, 50.0);
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
   glMaterialfv(GL_FRONT, GL_EMISSION, unset);
   glutSolidSphere(3.0, 36, 36);
   glPopMatrix();

   glPushMatrix();
   glTranslatef (40, 40, 50.0);
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
   glMaterialfv(GL_FRONT, GL_EMISSION, unset);
   glutSolidSphere(3.0, 36, 36);
   glPopMatrix();*/
}

void drawMegastructure(){

	mega->draw();
	glPushMatrix();{
		//glTranslatef(19.1,-1.0,4);
		//glRotatef(180,0,0,1);
		//glScalef(1.55,1.5,2.2);

		glTranslatef(18.5,-1.0,4);
		glRotatef(180,0,0,1);
		glScalef(1.5,1.5,1.5);
		base->base();
	}	
}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	//glClearColor(1,1,1,0);	//color white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glShadeModel(GL_SMOOTH);
	
	/********************
	/ set-up camera here
	********************/ 
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(100*cos(cameraAngle), 100*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	//gluLookAt(0,-1,150,	0,0,0,	0,0,1);
	gluLookAt(camera.getPosition().getX(),camera.getPosition().getY(),camera.getPosition().getZ(),
               camera.LookAtPosition().getX(),camera.LookAtPosition().getY(),camera.LookAtPosition().getZ(),
                camera.getUp().getX(),camera.getUp().getY(),camera.getUp().getZ()
           );
	
	
	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);
	

	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	lighting();
	draw_skybox();

	drawAxes();
	//drawGrid();
	glColor3f(1,1,1);

	
	//drawsphere(20,20,20);
	//glRotatef(180,1,0,0);
	//drawsphere(20,20,20);
	
	
	//drawss();
	//drawObjects(50, 10);
	//drawBouncingBall();
	//drawCuboid(cubeSide, cubeRadius);
	//drawRobotArm();
	drawMegastructure();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}



void animate(){
	angle+=0.05;
	updateVelocity();
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}


void init(){
	//codes for initialization
	drawgrid=1;
	drawaxes=1;
	cameraAngle = 0;	//// init the cameraAngle
	cameraAngleDelta = 0.002;
	rectAngle = 0;
	//canDrawGrid = true;
	cameraHeight = 50;
	cameraRadius = 50;
	camera.front = I;
	camera.up = K;
	Vectors ob(J.getX()*-1,J.getY()*-1,J.getZ()*-1);

	camera.right = ob;

    Vectors obj(I.getX()*-1,I.getY()*-1,I.getZ()*-1);
    Vectors obj1(obj.getX()*50,obj.getY()*50,obj.getZ()*50);
    camera.position= obj1;
//	camera.position = Vectors(Vector((-I)*50));
    angle=0;


	IQuadric=gluNewQuadric();
	sky1=bitmaploader.loadBitmap("textures/sky.bmp", 35);
	glass_sky = bitmaploader.loadBitmap("textures/sky_clouds.bmp", 40);
	//clear the screen
	glClearColor(0,0,0,0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);
	
	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	10000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){

	glutInit(&argc,argv);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();
	mega = new megastructure();
	mega->set_glass_tex(glass_sky);
	//mega->initBitmaps();
	//mega->initTextureSize();
	base = new Base();
	//base->initialize();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}

