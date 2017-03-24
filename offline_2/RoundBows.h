#pragma once
#include "Headers.h"

class RoundBows
{
public:

	struct point
	{
		double x,y,z;
	};

	bool is_texture_loaded;
	GLuint glass_texture_id;
	bitmapLoader loader;
	GLuint glass_sky;

	void load_texture();

	void set_glass_texture(GLuint tex_id);
	void draw_bows(double height, double radius, double width);
	void draw_straight_rods(double height, int number);
	void draw_rod(double length, double radius);
	void draw_round_rod(double arc, double radius, double thickness);
	void draw_top_room();
	void draw_floor(double angle_spread, double outer_radius, double inner_radius, double thickness);
	void draw_gapped_floor(double angle_spread, double outer_radius, double inner_radius, double thickness);
	void draw_cube(double length, double width, double height);
	void draw_surface(double length, double height);
	void draw_glass(double x1, double y1, double z1, double x2, double y2, double z2);
	void draw_extention(double height, double radius, double width);
	void draw_curved_glass(double height, double upper_radius, double lower_radius, GLuint tex_id);

	void draw();
	RoundBows(void);
	~RoundBows(void);
};

