#include "stdafx.h"
#include "MainPillar.h"


MainPillar::MainPillar(void)
{
	initialize();
}

MainPillar::~MainPillar(void)
{
}

void MainPillar::initialize()
{
	transform = new Transform();
	radius = 4;
	inclination = 0.0;
}

void MainPillar::draw()
{

	double radius = 4;

	double bottom_height = 150;
	double bottom_incline = 3.0;
	
	double offset_height = bottom_height;
	double middle_incline = 5.0;	
	double middle_height = 25;

	double top_offset = offset_height + middle_height;
	double top_height = 55;
	double top_incline = 0.0;
	
	//bottom pillars
	//printf("drawing bottom pillars\n");
	glPushMatrix();{
		glTranslatef(10.0,0.0,0.0);
		glRotatef(-bottom_incline,0,1,0);
		draw_pillar(bottom_height,radius);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-10.0,0.0,0.0);
		glRotatef(bottom_incline,0,1,0);
		draw_pillar(bottom_height,radius);
	}glPopMatrix();

	//middle pillars
	//printf("drawing middle pillars\n");
	glPushMatrix();{
		glTranslatef(-2,0.0,offset_height);
		glRotatef(middle_incline,0,1,0);
		draw_pillar(middle_height,radius);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(2,0.0,offset_height);
		glRotatef(-middle_incline,0,1,0);
		draw_pillar(middle_height,radius);
	}glPopMatrix();

	//top pillar
	glPushMatrix();{
		glTranslatef(0.0,0.0,top_offset);
		glRotatef(0,0,1,0);
		draw_top(top_height,radius);
	}glPopMatrix();

	//inner pillar
	double inner_offset = 110;
	double inner_pillar_height = 8;
	glPushMatrix();{
		glTranslatef(0.0,0.0,inner_offset);
		glRotatef(0,0,1,0);
		draw_inner_pillar(8, 3.8);
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(0.0,0.0,inner_offset + inner_pillar_height);
		glRotatef(0,0,1,0);
		draw_pillar(40, 3.8);
	}glPopMatrix();

	//draw bridges

	double bridge_height = 23;
	double bridge_x = 5;
	double bridge_y = 1.2;
	double bridge_z = 3;
	int i;

	for(i=1;i<5;i++)
	{
		glPushMatrix();{
			glTranslatef(0.0,-bridge_y,bridge_height * i + 10);
			glRotatef(0,0,1,0);
			draw_bridge(bridge_x,bridge_y,bridge_z);
		}glPopMatrix();
	}
}

void MainPillar:: draw_pillar(double height, double radius)
{
	const int MAX = 20;
	struct point points[MAX][MAX];
	int i,j;
	int turn = 0;
	int stacks = 2;
	int slices = 6;
	//double height = 150;
	//double radius = 4;
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
			/*if(turn == 0)glColor3f(1,1,1);
			else glColor3f(0.5,0.5,0.5);
			turn = (turn + 1)%2;*/
			
			glColor3f(1,1,1);
			glBegin(GL_QUADS);{
				glNormal3f(0.0f, 0.0f, 1.0f);
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
				
			}glEnd();
		}
		
	}
}

void MainPillar::draw_top(double height, double radius)
{
	const int MAX = 20;
	struct point points[MAX][MAX];
	int i,j;
	int turn = 0;
	int stacks = 2;
	int slices = 6;
	//double height = 150;
	//double radius = 4;
	double h,r;
	for(i=0;i<=stacks;i++)
	{
		h = height * cos(((double)i/(double)stacks)*(pi/2));
		//r = radius * cos((h/height)*(pi/2));
		r = ((height - h)/height) * radius;
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
			/*if(turn == 0)glColor3f(1,1,1);
			else glColor3f(0.5,0.5,0.5);
			turn = (turn + 1)%2*/
			glColor3f(1,1,1);
			glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
				
			}glEnd();
		}
		
	}
}

void draw_surface(double a, double b)
{
	glColor3f(0.8,0.8,0.8);
	glBegin(GL_QUADS);{
		glVertex3f( a, b,0);
		glVertex3f( a,-b,0);
		glVertex3f(-a,-b,0);
		glVertex3f(-a, b,0);
	}glEnd();
}

void MainPillar::draw_bridge(double l, double b, double h)
{
	glPushMatrix();{
		glTranslatef(0, 0, h);
		glRotatef(0,0,0,1);
		draw_surface(l,b);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(0, 0, -h);
		glRotatef(0,0,0,1);
		draw_surface(l,b);
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(0, b, 0);
		glRotatef(90,1,0,0);
		draw_surface(l, h);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(0, -b, 0);
		glRotatef(90,1,0,0);
		draw_surface(l, h);
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(l, 0, 0);
		glRotatef(90,0,1,0);
		draw_surface(h, b);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-l, 0, 0);
		glRotatef(90,0,1,0);
		draw_surface(h, b);
	}glPopMatrix();
	
}

void MainPillar::draw_inner_pillar(double height, double radius)
{
	const int MAX = 20;
	struct point points[MAX][MAX];
	int i,j;
	int turn = 0;
	int stacks = 2;
	int slices = 6;
	//double height = 150;
	//double radius = 4;
	double h,r;
	for(i=0;i<=stacks;i++)
	{
		h = height * cos(((double)i/(double)stacks)*(pi/2));
		//r = radius * cos((h/height)*(pi/2));
		r = (h/height) * radius;
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
			glColor3f(0.8,0.8,0.8);
			glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
				
			}glEnd();
		}
		
	}

}