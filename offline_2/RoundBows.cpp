#include "stdafx.h"
#include "RoundBows.h"


bool isF = true;
static bool is_texture_loaded = false;

RoundBows::RoundBows(void)
{
	
	if(!is_texture_loaded){
		load_texture();
		is_texture_loaded = true;
	}
	
}

RoundBows::~RoundBows(void)
{
}

void RoundBows::load_texture()
{
	
	glass_texture_id = loader.loadBitmap("textures/sky_clouds.bmp", 30);
	printf("texture loaded %d\n",glass_texture_id);
}

void RoundBows::set_glass_texture(GLuint tex_id)
{
	glass_sky = tex_id;
}
void RoundBows::draw()
{

	double bow_height = 70;
	double bow_offset = 40;
	double bow_radius = 25;
	double bow_incline = 35;

	//upper bows
	glPushMatrix();{
		glTranslatef(0.0,0,bow_height + bow_offset);
		glRotatef(180 + bow_incline,0,0,1);
		draw_bows(bow_height,bow_radius,2);
	}glPopMatrix();	

	glPushMatrix();{
		glTranslatef(0.0,0,bow_height + bow_offset);
		glRotatef(180 - bow_incline,0,0,1);
		draw_bows(bow_height,bow_radius,2);
	}glPopMatrix();

	//lower extension bows
	double extention_offset = 20;
	double extension_radius = bow_radius;
	double extension_incline = bow_incline - 3;
	glPushMatrix();{
		glColor3f(0.4,0.6,0);
		glTranslatef(0,0,-extention_offset);
		glRotatef(extension_incline,0,0,1);
		draw_extention(bow_offset + extention_offset,extension_radius,2);
	}glPopMatrix();	

	glPushMatrix();{
		glColor3f(0.4,0.6,0);
		glTranslatef(0,0,-extention_offset);
		glRotatef(-extension_incline,0,0,1);
		draw_extention(bow_offset + extention_offset,extension_radius,2);
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(0.0,0,0);
		glRotatef(0,0,0,1);
		draw_straight_rods(100, 11);
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(0.0,0,0);
		glRotatef(0,0,0,1);
		draw_top_room();
	}glPopMatrix();
}

void RoundBows::draw_bows(double height, double radius, double width)	
{
	const int MAX = 50;
	point outer_surface[MAX][2];
	point inner_surface[MAX][2];

	int i,j;
	int stacks = 40;
	int slices = 2;
	double h,r;
	for(i=0;i<=stacks;i++)
	{
		h = height*cos(((double)i/(double)(stacks))*(pi));
		//if(isF)printf("height: %lf\n",h);
		r = radius * cos((h/height)*(pi/2));
		outer_surface[i][0].x = -width/2;
		outer_surface[i][1].x = width/2;
		outer_surface[i][0].y = r;
		outer_surface[i][1].y = r;
		outer_surface[i][0].z=h;
		outer_surface[i][1].z=h;

		h = (height - 20)*cos(((double)i/(double)(stacks))*(pi));
		r = (radius) * cos((h/height)*(pi/2)) - 5;
		inner_surface[i][0].x = -width/2;
		inner_surface[i][1].x = width/2;
		inner_surface[i][0].y = r;
		inner_surface[i][1].y = r;
		inner_surface[i][0].z=h;
		inner_surface[i][1].z=h;
	}
	j = 0;
	
	for(i=0;i<stacks;i++)
	{
		glColor3f(1,1,1);
		glBegin(GL_QUADS);{
			glVertex3f(outer_surface[i][j].x,outer_surface[i][j].y,outer_surface[i][j].z);
			glVertex3f(outer_surface[i][j+1].x,outer_surface[i][j+1].y,outer_surface[i][j+1].z);
			glVertex3f(outer_surface[i+1][j+1].x,outer_surface[i+1][j+1].y,outer_surface[i+1][j+1].z);
			glVertex3f(outer_surface[i+1][j].x,outer_surface[i+1][j].y,outer_surface[i+1][j].z);
				
		}glEnd();

		//glColor3f(1,0,1);
		glBegin(GL_QUADS);{
			glVertex3f(inner_surface[i][j].x,inner_surface[i][j].y,inner_surface[i][j].z);
			glVertex3f(inner_surface[i][j+1].x,inner_surface[i][j+1].y,inner_surface[i][j+1].z);
			glVertex3f(inner_surface[i+1][j+1].x,inner_surface[i+1][j+1].y,inner_surface[i+1][j+1].z);
			glVertex3f(inner_surface[i+1][j].x,inner_surface[i+1][j].y,inner_surface[i+1][j].z);
				
		}glEnd();

		glColor3f(0.8,0.8,0.8);
		glBegin(GL_QUADS);{
			glVertex3f(outer_surface[i][j].x,outer_surface[i][j].y,outer_surface[i][j].z);
			glVertex3f(inner_surface[i][j].x,inner_surface[i][j].y,inner_surface[i][j].z);
			glVertex3f(inner_surface[i+1][j].x,inner_surface[i+1][j].y,inner_surface[i+1][j].z);
			glVertex3f(outer_surface[i+1][j].x,outer_surface[i+1][j].y,outer_surface[i+1][j].z);			
				
		}glEnd();

		glBegin(GL_QUADS);{
			glVertex3f(outer_surface[i][j+1].x,outer_surface[i][j+1].y,outer_surface[i][j+1].z);
			glVertex3f(inner_surface[i][j+1].x,inner_surface[i][j+1].y,inner_surface[i][j+1].z);
			glVertex3f(inner_surface[i+1][j+1].x,inner_surface[i+1][j+1].y,inner_surface[i+1][j+1].z);
			glVertex3f(outer_surface[i+1][j+1].x,outer_surface[i+1][j+1].y,outer_surface[i+1][j+1].z);			
				
		}glEnd();
	}
	isF = false;

}

void RoundBows::draw_extention(double height, double radius, double width)
{
	const int MAX = 50;
	point outer_surface[MAX][2];
	point inner_surface[MAX][2];

	double outer_radius = radius + 10;
	double inner_radius = radius - 5;
	double outer_height = height + 0;
	double inner_height = height + 0;
	double arc_angle = pi/2;
	int stack_gap = 10;
	int i,j;
	int stacks = 40;
	int slices = 2;
	double h,r;
	double outer_angle = acos(outer_height/outer_radius);
	double inner_angle = acos(inner_height/inner_radius);

	//printf("outer angle = %lf inner angle = %lf\n",outer_angle, inner_angle);
	outer_angle = 43*pi/180;
	inner_angle = 20*pi/180;

	for(i=0;i<=stacks;i++)
	{
		h = outer_height*cos(((double)i/(double)(stacks ))*(arc_angle));
		//r = outer_radius * cos((h/outer_height)*(pi/2));
		r = abs(outer_height - h)*tan(outer_angle);
		//printf("r = %lf h = %lf \n",r,h);
		outer_surface[i][0].x = -width/2;
		outer_surface[i][1].x = width/2;
		outer_surface[i][0].y = r;
		outer_surface[i][1].y = r;
		outer_surface[i][0].z=h;
		outer_surface[i][1].z=h;

		h = (inner_height)*cos(((double)i/(double)(stacks ))*(arc_angle));
		//r = (inner_radius) * cos((h/inner_height)*(pi/2)) - 5;
		r = abs(inner_height - h)*tan(inner_angle);
		//printf("r = %lf h = %lf \n",r,h);
		inner_surface[i][0].x = -width/2;
		inner_surface[i][1].x = width/2;
		inner_surface[i][0].y = r;
		inner_surface[i][1].y = r;
		inner_surface[i][0].z=h;
		inner_surface[i][1].z=h;
	}
	j = 0;
	
	for(i=0;i<stacks;i++)
	{
		glColor3f(1,1,1);
		glBegin(GL_QUADS);{
			glVertex3f(outer_surface[i][j].x,outer_surface[i][j].y,outer_surface[i][j].z);
			glVertex3f(outer_surface[i][j+1].x,outer_surface[i][j+1].y,outer_surface[i][j+1].z);
			glVertex3f(outer_surface[i+1][j+1].x,outer_surface[i+1][j+1].y,outer_surface[i+1][j+1].z);
			glVertex3f(outer_surface[i+1][j].x,outer_surface[i+1][j].y,outer_surface[i+1][j].z);
				
		}glEnd();

		//glColor3f(1,0,1);
		glBegin(GL_QUADS);{
			glVertex3f(inner_surface[i][j].x,inner_surface[i][j].y,inner_surface[i][j].z);
			glVertex3f(inner_surface[i][j+1].x,inner_surface[i][j+1].y,inner_surface[i][j+1].z);
			glVertex3f(inner_surface[i+1][j+1].x,inner_surface[i+1][j+1].y,inner_surface[i+1][j+1].z);
			glVertex3f(inner_surface[i+1][j].x,inner_surface[i+1][j].y,inner_surface[i+1][j].z);
				
		}glEnd();

		//glColor3f(0.8,0.8,0.8);
		glColor3f(1,1,1);
		glBegin(GL_QUADS);{
			glVertex3f(outer_surface[i][j].x,outer_surface[i][j].y,outer_surface[i][j].z);
			glVertex3f(inner_surface[i][j].x,inner_surface[i][j].y,inner_surface[i][j].z);
			glVertex3f(inner_surface[i+1][j].x,inner_surface[i+1][j].y,inner_surface[i+1][j].z);
			glVertex3f(outer_surface[i+1][j].x,outer_surface[i+1][j].y,outer_surface[i+1][j].z);			
				
		}glEnd();

		glBegin(GL_QUADS);{
			glVertex3f(outer_surface[i][j+1].x,outer_surface[i][j+1].y,outer_surface[i][j+1].z);
			glVertex3f(inner_surface[i][j+1].x,inner_surface[i][j+1].y,inner_surface[i][j+1].z);
			glVertex3f(inner_surface[i+1][j+1].x,inner_surface[i+1][j+1].y,inner_surface[i+1][j+1].z);
			glVertex3f(outer_surface[i+1][j+1].x,outer_surface[i+1][j+1].y,outer_surface[i+1][j+1].z);			
				
		}glEnd();
	}
	isF = false;
}

void RoundBows::draw_straight_rods(double height, int number)
{

	double rod_angle = 15.0;
	int rod_numbers = 8;
	double rod_offset = 80;
	double gap = 8;
	double angle_gap = 2.3;
	double rod_length = 15, trans_x_offset = 5.3, rod_inc = 0.8 + 0.1, trans_x_dec = 0.3;
	double rod_radius = 20;
	double rod_arc = 400;
	double bow_radius = 25;
	double round_rod_offset = -17;
	int i;
	for(i=0;i<rod_numbers;i++)
	{
		double sin_value = sin(((double)i/(double)(9))*pi);
		
		glPushMatrix();{
			//glColor3f(0.8,0.8,0.8);
			glColor3f(1,1,1);
			glTranslatef(trans_x_offset - i*trans_x_dec,0,rod_offset + gap*i);
			glRotatef(rod_angle + i*angle_gap*sin_value,0,0,1);
			draw_rod(rod_length + i*rod_inc*sin_value,0.5);			
		}glPopMatrix();

		glPushMatrix();{
			//glColor3f(0.8,0.8,0.8);
			glColor3f(1,1,1);
			glTranslatef(-trans_x_offset + i*trans_x_dec,0,rod_offset + gap*i);
			glRotatef(-(rod_angle + i*angle_gap*sin_value),0,0,1);
			draw_rod(rod_length + i*rod_inc*sin_value,0.5);
		}glPopMatrix();

		glPushMatrix();{
			glColor3f(1,1,1);
			if(i>5){
				round_rod_offset += 1;
			}
			glTranslatef(0,round_rod_offset - 5*sin_value,rod_offset + gap*i);
			draw_round_rod(10 + sin_value, rod_length + i*rod_inc*sin_value, 1);
		}glPopMatrix();
	}

	
}

void RoundBows::draw_rod(double length, double radius)
{
	const int MAX = 50;
	point points[MAX][MAX];
	int i,j;
	int stacks = 30;
	int slices = 10;
	double height = length;
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

	glPushMatrix();{
		glRotatef(90,1,0,0);
		for(i=0;i<stacks;i++)
		{
			for(j=0;j<slices;j++)
			{
				glColor3f(1,1,1);
				GLfloat white[] = {1.0,1.0,1.0,1.0f};
				glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
				glMaterialfv(GL_FRONT, GL_SPECULAR, white);
				GLfloat shininess[] = {50};
				glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
				glBegin(GL_QUADS);{
					//glNormal3f(0,0,1);
					glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
					glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
					glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
					glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
				
				}glEnd();
			}		
		}
	}glPopMatrix();	
}

void RoundBows::draw_round_rod(double arc, double radius, double thickness)
{
	const int MAX  = 50;
	point points[MAX][20];

	int i,j;
	int stacks = 20;
	int slices = 15;
	double h;
	double r;
	double k;

	double b = radius*cos(asin((arc/2)/radius));

	for(i=0;i<=stacks;i++)
	{
		h = arc*cos(((double)i/(double)stacks)*pi);
		r = thickness;
		k = radius*cos(asin((h)/radius)) - b;
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi) + k;
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;

		}
	}
	
	glPushMatrix();{
		glRotatef(90,1,0,0);
		glRotatef(-90,0,1,0);
		for(i=0;i<stacks;i++)
		{
			for(j=0;j<slices;j++)
			{
				//glColor3f(1,1,1);
				glColor3f(1,1,1);
				GLfloat white[] = {1.0,1.0,1.0,1.0f};
				glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
				glMaterialfv(GL_FRONT, GL_SPECULAR, white);
				GLfloat shininess[] = {50};
				glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
				glBegin(GL_QUADS);{
					//glNormal3f(0,0,1);
					glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
					glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
					glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
					glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
				
				}glEnd();
			}		
		}
	}glPopMatrix();	

}



void RoundBows::draw_top_room()
{
	//1. draw sode rods (3)
	//2. draw round rods (4)
	//3. draw floors
	//4. draw glass

	int i;
	double floor_offset = 145;
	double rod_length = 12, rod_inc = 2;
	double rod_offset = floor_offset, gap = 5;
	double trans_x_offset = 2.2, trans_x_dec = -0.1;
	
	double rod_angle = 28, angle_gap = 3;

	for(i=0;i<3;i++)
	{
		glColor3f(0.8,0.8,0.8);
		glPushMatrix();{
			glTranslatef(trans_x_offset + i*trans_x_dec,0,rod_offset + gap*i);
			glRotatef(rod_angle - i*angle_gap,0,0,1);
			draw_rod(rod_length - i*rod_inc,0.5);
			
			//glass drawing
			double force_height = 0;
			double force_x = 0;
			if(i > 1){
				force_height = 5;
				force_x = 3;
			}

			glPushMatrix();{
				glColor4f(0,0,1,0.8);
				glRotatef(-90,0,0,1);
				glBegin(GL_QUADS);{
					glVertex3f(0, 0, 0);
					glVertex3f(rod_length - i*rod_inc, 0, 0);
					glVertex3f(rod_length - (i+1)*rod_inc - force_x, 0, gap + force_height);
					glVertex3f(0, 0, gap);				
				}glEnd();
			}glPopMatrix();

		}glPopMatrix();
		
		glColor3f(0.8,0.8,0.8);
		glPushMatrix();{
			glTranslatef(-trans_x_offset - i*trans_x_dec,0,rod_offset + gap*i);
			glRotatef(-(rod_angle - i*angle_gap),0,0,1);
			draw_rod(rod_length - i*rod_inc,0.5);

			//glass drawing
			double force_height = 0;
			double force_x = 0;
			if(i > 1){
				force_height = 5;
				force_x = 3;
			}

			glPushMatrix();{
				glColor4f(0,0,1,0.8);
				glRotatef(-90,0,0,1);
				glBegin(GL_QUADS);{
					glVertex3f(0, 0, 0);
					glVertex3f(rod_length - i*rod_inc, 0, 0);
					glVertex3f(rod_length - (i+1)*rod_inc - force_x, 0, gap + force_height);
					glVertex3f(0, 0, gap);				
				}glEnd();
			}glPopMatrix();

		}glPopMatrix();

		
	}

	double round_rod_offset = -17;
	double round_rod_dec = 2.9;

	for(i=0;i<4;i++)
	{
		glPushMatrix();{
			glColor3f(1,1,1);
			glTranslatef(0,round_rod_offset + i*round_rod_dec,rod_offset + gap*i);
			draw_round_rod(9 - i*1.2 , rod_length + i*rod_inc, 1);
		}glPopMatrix();
	}

	for(i=1;i<3;i++)
	{
		glColor3f(0.9,0.9,0.9);
		glPushMatrix();{
			glTranslatef(0,6,rod_offset + gap*i);
			glRotatef(0,0,0,1);
			draw_floor(47,10+rod_length - i*rod_inc,7,1);		
		}glPopMatrix();
	}

	glPushMatrix();{
		glTranslatef(0,0,rod_offset);
		draw_gapped_floor(47, 10+rod_length,7,1);
	}glPopMatrix();

	glPushMatrix();{
		glColor4f(0,0,1,0.5);
		glTranslatef(0,-5,floor_offset);
		glRotatef(0,0,0,1);
		draw_curved_glass(gap*3 + 0.5,rod_length - 3*rod_inc - 2, rod_length + 1, glass_sky);
	}glPopMatrix();
}

void RoundBows::draw_floor(double angle_spread, double outer_radius, double inner_radius, double thickness)
{
	const int MAX  = 50;
	point points[MAX][2][2];

	double radian_spread = angle_spread*pi/180;

	int i,j;
	int slices = 20;

	for(i=0;i<slices;i++)
	{
		points[i][0][0].x = outer_radius*cos(((double)i/(double)slices)*radian_spread);
		points[i][0][0].y = outer_radius*sin(((double)i/(double)slices)*radian_spread);
		points[i][0][0].z = thickness/2;

		points[i][0][1].x = outer_radius*cos(((double)i/(double)slices)*radian_spread);
		points[i][0][1].y = outer_radius*sin(((double)i/(double)slices)*radian_spread);
		points[i][0][1].z = -thickness/2;

		points[i][1][0].x = inner_radius*cos(((double)i/(double)slices)*radian_spread);
		points[i][1][0].y = inner_radius*sin(((double)i/(double)slices)*radian_spread);
		points[i][1][0].z = thickness/2;

		points[i][1][1].x = inner_radius*cos(((double)i/(double)slices)*radian_spread);
		points[i][1][1].y = inner_radius*sin(((double)i/(double)slices)*radian_spread);
		points[i][1][1].z = -thickness/2;
	}

	j = 0;
	for(i=0;i<slices - 1;i++)
	{
		glPushMatrix();
		{
			glRotatef(-90-angle_spread/2,0,0,1);
			glBegin(GL_QUADS);{
				glVertex3f(points[i][j][0].x,points[i][j][0].y,points[i][j][0].z);
				glVertex3f(points[i][j+1][0].x,points[i][j+1][0].y,points[i][j+1][0].z);
				glVertex3f(points[i+1][j+1][0].x,points[i+1][j+1][0].y,points[i+1][j+1][0].z);
				glVertex3f(points[i+1][j][0].x,points[i+1][j][0].y,points[i+1][j][0].z);
				
			}glEnd();

			glBegin(GL_QUADS);{
				glVertex3f(points[i][j][1].x,points[i][j][1].y,points[i][j][1].z);
				glVertex3f(points[i][j+1][1].x,points[i][j+1][1].y,points[i][j+1][1].z);
				glVertex3f(points[i+1][j+1][1].x,points[i+1][j+1][1].y,points[i+1][j+1][1].z);
				glVertex3f(points[i+1][j][1].x,points[i+1][j][1].y,points[i+1][j][1].z);
				
			}glEnd();
		}glPopMatrix();
		
	}
}

void RoundBows::draw_surface(double a, double b)
{
	glBegin(GL_QUADS);{
		glVertex3f( a, b,0);
		glVertex3f( a,-b,0);
		glVertex3f(-a,-b,0);
		glVertex3f(-a, b,0);
	}glEnd();
}

void RoundBows::draw_cube(double l, double b, double h)
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

void RoundBows::draw_gapped_floor(double angle_spread, double outer_radius, double inner_radius, double thickness)
{
	double surface_length = 2;
	double surface_width = 5;
	double surface_thickness = thickness/2;

	glPushMatrix();{
		glTranslated(0,-5,0);
		draw_cube(surface_length,surface_width,surface_thickness);
	}glPopMatrix();

	int i;
	double layer_1 = 11;
	double layer_2 = 2;
	glPushMatrix();{
		glTranslatef(-surface_length,-layer_1,0);

		for(i=0;i<5;i++)
		{
			glPushMatrix();{
				glTranslatef(i*surface_width/5,0,0);				
				draw_cube(0.1,layer_2,surface_thickness);
			}glPopMatrix();
		}

	}glPopMatrix();

	double layer_3_length = 2;
	double layer_3 = layer_1 + layer_2 + layer_3_length;
	glPushMatrix();{
		glTranslatef(0,-layer_3,0);
		draw_cube(2,layer_3_length,surface_thickness);
	}glPopMatrix();

	double s_angle = 30;
	glPushMatrix();{
		glTranslatef(surface_length,0,0);
		glRotatef(s_angle/2,0,0,1);
		draw_floor(s_angle,outer_radius - 5.2, inner_radius - 5,thickness);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-surface_length + 0.35,0,0);
		glRotatef(-s_angle/2,0,0,1);
		draw_floor(s_angle,outer_radius - 5.2, inner_radius - 5,thickness);
	}glPopMatrix();
}

void RoundBows::draw_curved_glass(double height, double upper_radius, double lower_radius, GLuint tex_id)
{
	const int MAX = 50;
	point points[50][2];

	int i;
	int slices = 20;
	double spread = 105;
	spread = spread*pi/180;

	//printf("%lf %lf\n",lower_spread, upper_spread);

	for(i=0;i<slices;i++)
	{
		points[i][0].x = lower_radius*cos(((double)i/(double)slices)*spread);
		points[i][0].y = lower_radius*sin(((double)i/(double)slices)*spread);
		points[i][0].z = 0;

		points[i][1].x = upper_radius*cos(((double)i/(double)slices)*(spread));
		points[i][1].y = upper_radius*sin(((double)i/(double)slices)*(spread));
		points[i][1].z = height;
	}
	
	int j = 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glNormal3f(0.0,0.0,1.0);
	glColor4f(1,1,1,0.5);
	glDepthMask(0);
	double fraction = 1/slices;
	for(i=0;i<slices - 1;i++)
	{
		glPushMatrix();
		{
			glRotatef(-90 - spread*90/pi,0,0,1);
			/*glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);				
			}glEnd();*/

			
			/*glBegin(GL_POLYGON);
			glTexCoord2f(fraction*i,0); glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
			glTexCoord2f(fraction*i,1); glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glTexCoord2f(fraction*(i+1),1); glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glTexCoord2f(fraction*(i+1),0); glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
			glEnd();*/

			glBegin(GL_POLYGON);
			glTexCoord2f(fraction*i*cos(((double)i/(double)slices)),0); glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
			glTexCoord2f(fraction*i*cos(((double)i/(double)slices)),1*sin(((double)i/(double)slices))); glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
			glTexCoord2f(fraction*(i+1)*cos(((double)i/(double)slices)),1*sin(((double)i/(double)slices))); glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
			glTexCoord2f(fraction*(i+1)*cos(((double)i/(double)slices)),0); glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
			glEnd();
		}glPopMatrix();		
	}
	glDepthMask(1);
	glDisable(GL_TEXTURE_2D);
}


