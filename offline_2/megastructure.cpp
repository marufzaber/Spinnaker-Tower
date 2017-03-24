#include "stdafx.h"
#include "megastructure.h"




megastructure::megastructure(void)
{
	printf("mega constructor\n");
	quadric = gluNewQuadric();
	initBitmaps();
	initTextureSize();
	/*pillar = new MainPillar();	
	pillar->initialize();

	round_bows = new RoundBows();
	round_bows->load_texture();*/
}


megastructure::~megastructure()
{
}

void megastructure::initBitmaps()
{
	base_texture_id = bitmapLoader.loadBitmap("textures/base_texture.bmp", 100);
	//printf("loaded texture: %d\n",base_texture_id);
	//printf("texture loaded 100\n");
}

void megastructure::initTextureSize()
{
	base_width = BASE_WIDTH/8;
	base_height = BASE_HEIGHT/8;
}

void megastructure::draw_base()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->base_texture_id);
	glNormal3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0,0.0);glVertex3f(-1*base_width,-1*base_height,0.0);
	glTexCoord2f(0.0,1.0);glVertex3f(-1*base_width,base_height,0.0);
	glTexCoord2f(1.0,1.0);glVertex3f(base_width,base_height,0.0);
	glTexCoord2f(1.0,0.0);glVertex3f(base_width,-1*base_height,0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void megastructure::set_glass_tex(GLuint tex_id)
{
	glass_tex_id = tex_id;
}

void megastructure::draw_pillers()
{
	MainPillar *pillar = new MainPillar();
	RoundBows *round_bows = new RoundBows();
	round_bows->set_glass_texture(glass_tex_id);
	glNormal3f(0.0f, 0.0f, 1.0f);
	
	glPushMatrix();{
		glTranslatef(0,0,10);
		pillar->draw();
		round_bows->draw();
	}glPopMatrix();
}

void megastructure::draw()
{
	draw_base();
	draw_pillers();
}
