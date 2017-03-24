#include "stdafx.h"
#include "Base.h"


Base::Base(void)
{
	count = 0;
	initialize();
}


Base::~Base(void)
{
}

void Base::drawsphere(float radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	h=0;

	for(i=0;i<=stacks;i++)
	{

		//h=radius*sin(((double)i/(double)stacks)*(pi/2));

		r=radius;
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
		h+=1;

	}
	for(i=0;i<stacks;i++)
	{

		for(j=0;j<slices;j++)
		{

			glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

			}glEnd();
		}
	}
}

void Base::drawFilledCircle(float x, float y, float radius){
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	float twicePi = 2.0f * 3.1416* (821.0/3600.0);

	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texid);
    glNormal3f(1.0,0.0,0.0);
	glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0,0);glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
		    X[i]=x + (radius * cos(i *  twicePi / triangleAmount));
		    Y[i]=y + (radius * sin(i * twicePi / triangleAmount));

			glTexCoord2f(.5 * cos(i *  twicePi / triangleAmount),.5 * sin(i * twicePi / triangleAmount));glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Base::dr(){
    glPushMatrix();{

        glPushMatrix();{

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,texid);
            glNormal3f(1.0,0.0,0.0);


            glBegin(GL_POLYGON);{
                glTexCoord2f(0,0);glVertex3f(7.095,-10.782,0);
                glTexCoord2f(1,0);glVertex3f(12.367,-10.782,0);
                glTexCoord2f(1,1);glVertex3f(12.367,-17.215,0);
                glTexCoord2f(0,1);glVertex3f(3.388,-17.215,0);

            }glEnd();

            glBegin(GL_POLYGON);{
               glTexCoord2f(0,0); glVertex3f(6.012,-10.782,0);
               glTexCoord2f(1,0); glVertex3f(7.095,-10.782,0);
               glTexCoord2f(1,1); glVertex3f(6.9,-11.102,0);
            }glEnd();

            glBegin(GL_POLYGON);{
               glTexCoord2f(0,0); glVertex3f(3.388,-10.782,0);
                glTexCoord2f(1,0);glVertex3f(6.012,-10.782,0);
                glTexCoord2f(1,1);glVertex3f(5.088,-12.382,0);
            }glEnd();

            glBegin(GL_POLYGON);{
            glTexCoord2f(0,0);glVertex3f(1.607,-2.695,0);
            glTexCoord2f(1,0);glVertex3f(3.388,-10.782,0);
            glTexCoord2f(1,1);glVertex3f(12.367,-10.782,0);

            glTexCoord2f(0,1);glVertex3f(12.367,-2.695,0);
        }glEnd();
        glDisable(GL_TEXTURE_2D);
		}glPopMatrix();


        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texid);
        glNormal3f(1.0,0.0,0.0);

		glPushMatrix();{
            glTexCoord2f(0,0);glBegin(GL_POLYGON);{
            glTexCoord2f(0,1);glVertex3f(0,0,0);
            glTexCoord2f(1,1);glVertex3f(1.607,-2.695,0);
            glTexCoord2f(1,.5);glVertex3f(12.367,-2.695,0);
            glTexCoord2f(1,0);glVertex3f(12.367,0,0);
        }glEnd();
		}glPopMatrix();


		glPushMatrix();{
            glBegin(GL_POLYGON);{
            glTexCoord2f(0,0);glVertex3f(0,0,0);
            glTexCoord2f(0,1);glVertex3f(7.284,13.782,0);
            glTexCoord2f(1,1);glVertex3f(12.367,13.782,0);
            glTexCoord2f(1,0);glVertex3f(12.367,0,0);
        }glEnd();
		}glPopMatrix();
        glDisable(GL_TEXTURE_2D);

	}glPopMatrix();
}

void Base::drawHorizontalGrill(){

    glPushMatrix();{
    glScalef(1,1,.0475);
    drawsphere(.07,20,20);
    }glPopMatrix();

    int i=0;
    float x=0;
    for(i=0;i<11;i++){
            float y=((x-0)*(0-13.782)/(0-7.284));
            glPushMatrix();{
                glTranslatef(x,y,0);
                glScalef(1,1,.0475);
                drawsphere(.07,20,20);
            }glPopMatrix();
            x+=.66218182;
    }

    x=7.284;
    for(i=0;i<5;i++){
            float y=13.782;
            glPushMatrix();{
                glTranslatef(x,y,0);
                glScalef(1,1,.0475);
                drawsphere(.07,20,20);
            }glPopMatrix();
            x+=1.27075;
    }
    x=0;

    for(i=0;i<4;i++){
            float y=((x-0)*(0+2.695)/(0-1.607));
            glPushMatrix();{
                glTranslatef(x,y,0);
                glScalef(1,1,.0475);
                drawsphere(.07,20,20);
            }glPopMatrix();
            x+=.535666666;
    }

    x=1.607;

    for(i=0;i<8;i++){
            float y=((x-1.607)*(-2.695+10.782)/(1.607-3.388))-2.695;

            glPushMatrix();{
                glTranslatef(x,y,0);
                glScalef(1,1,.0475);
                drawsphere(.07,20,20);
            }glPopMatrix();
            x+=.246855952;
    }


    for(i=0;i<3;i++){
            float y=((x-3.388)*(-10.782+12.382)/(3.388-5.088))-10.782;

            glPushMatrix();{
                glTranslatef(x,y,0);
                glScalef(1,1,.0475);
                drawsphere(.07,20,20);
            }glPopMatrix();
            x+=.75;
    }



}

void Base::drawFilledCirclewithSide(){


     //  glColor3f(0,0,1) ;
    for(int i=0;i<20;i++){
          glColor3f(1,1,1);
          if(i==10||i==11){
              glColor3f(0,0,0);
              glBegin(GL_QUADS);{
                glTexCoord2f(0,0);glVertex3f(X[i],Y[i],-2.183);
                glTexCoord2f(0,1);glVertex3f(X[i],Y[i],4.506);
                glTexCoord2f(1,1);glVertex3f(X[i+1],Y[i+1],4.506);
                glTexCoord2f(1,0);glVertex3f(X[i+1],Y[i+1],-2.183);
               }
          }

        //  if(X[i]==0.0||(X[i]==0.0 && Y[i]==0.0))continue;
          glBegin(GL_QUADS);{
          glVertex3f(X[i],Y[i],-2.183);
          glVertex3f(X[i],Y[i],4.506);
          glVertex3f(X[i+1],Y[i+1],4.506);
          glVertex3f(X[i+1],Y[i+1],-2.183);
        }
    }

}

void Base::drawSurface(){

        glPushMatrix();{

        glPushMatrix();{
        glTranslatef(12,-6,0)    ;
        glRotatef(-130,0,0,1);
       // drawFilledCirclewithSide();
        drawFilledCircle(0.0,0,17.517);
        }glPopMatrix();

        glPushMatrix();{

        dr();
        glTranslatef(12.367,0,0);
        glRotatef(180,0,1,0);
        glTranslatef(-12.367,0,0);

        glPushMatrix();{
        dr();}glPopMatrix();
        }glPopMatrix();
    }glPopMatrix();

}

void Base::drawSide(int rev){

                glPushMatrix();{
                glColor3f(1,1,1);

            glBegin(GL_POLYGON);{

                glVertex3f(7.095,-10.782,0);
                glVertex3f(7.095,-10.782,4.506);
                glVertex3f(3.388,-17.215,4.506);
                glVertex3f(3.388,-17.215,0);

            }glEnd();

            glBegin(GL_POLYGON);{

                glVertex3f(6.012,-10.782,0);
                glVertex3f(6.012,-10.782,4.506);
                glVertex3f(6.9,-11.102,4.506);
                glVertex3f(6.9,-11.102,0);

            }glEnd();

            glBegin(GL_POLYGON);{
                glVertex3f(6.012,-10.782,0);
               glVertex3f(6.012,-10.782,4.506);
                glVertex3f(5.088,-12.382,4.506);
                glVertex3f(5.088,-12.382,0);
            }glEnd();

            glBegin(GL_POLYGON);{
                glVertex3f(3.388,-10.782,0);
                glVertex3f(3.388,-10.782,4.506);
                glVertex3f(5.088,-12.382,4.506);
                glVertex3f(5.088,-12.382,0);

            }glEnd();

            glEnable(GL_TEXTURE_2D);
            if(rev==0)
                glBindTexture(GL_TEXTURE_2D,upside1);
            else if (rev==1)glBindTexture(GL_TEXTURE_2D,upsideR1);
            glNormal3f(1.0,0.0,0.0);
            glBegin(GL_POLYGON);{
                glTexCoord2f(0,0);glVertex3f(1.607,-2.695,0);
                glTexCoord2f(0,1);glVertex3f(1.607,-2.695,4.506);
                glTexCoord2f(1,1);glVertex3f(3.388,-10.782,4.506);
                glTexCoord2f(1,0);glVertex3f(3.388,-10.782,0);
            }glEnd();
            glDisable(GL_TEXTURE_2D);

          glEnable(GL_TEXTURE_2D);
           if(rev==0)
                glBindTexture(GL_TEXTURE_2D,upside2);
            else if (rev==1)glBindTexture(GL_TEXTURE_2D,upsideR2);
            glNormal3f(1.0,0.0,0.0);
            glBegin(GL_POLYGON);{
               glTexCoord2f(0,0); glVertex3f(0,0,0);
               glTexCoord2f(0,1); glVertex3f(0,0,4.506);
               glTexCoord2f(1,1); glVertex3f(1.607,-2.695,4.506);
               glTexCoord2f(1,0); glVertex3f(1.607,-2.695,0);
            }glEnd();
            glDisable(GL_TEXTURE_2D);

           glEnable(GL_TEXTURE_2D);
           if(rev==0)
                glBindTexture(GL_TEXTURE_2D,upside4);
            else if (rev==1)glBindTexture(GL_TEXTURE_2D,upsideR4);
            glNormal3f(1.0,0.0,0.0);

		    glBegin(GL_POLYGON);{
		        glTexCoord2f(0,0);glVertex3f(12.367,13.782,0);
		        glTexCoord2f(0,1);glVertex3f(12.367,13.782,4.506);
                glTexCoord2f(1,1);glVertex3f(7.284,13.782,4.506);
                glTexCoord2f(1,0);glVertex3f(7.284,13.782,0);

		    }glEnd();
            glDisable(GL_TEXTURE_2D);

            glEnable(GL_TEXTURE_2D);
            if(rev==0)
                glBindTexture(GL_TEXTURE_2D,upside3);
            else if (rev==1)glBindTexture(GL_TEXTURE_2D,upsideR3);

            glNormal3f(1.0,0.0,0.0);
            glBegin(GL_POLYGON);{
                    glTexCoord2f(0,0);glVertex3f(0,0,0);
                    glTexCoord2f(0,1);glVertex3f(0,0,4.506);
                    glTexCoord2f(1,1);glVertex3f(7.284,13.782,4.506);
                    glTexCoord2f(1,0);glVertex3f(7.284,13.782,0);
                    }glEnd();
            }glPopMatrix();
            glDisable(GL_TEXTURE_2D);
}

void Base::drawGrill(){
    glPushMatrix();{
        glColor3f(.88,.88,.88);


        glPushMatrix();{
        glColor3f(.88,.88,.88);
            glTranslatef((7.284+5.083),13.782,5.456);
            glRotatef(-90,0,1,0);
            glScalef(1,1,.25415);
            drawsphere(.07,20,20);
        }glPopMatrix();

        glPushMatrix();{
         glColor3f(.88,.88,.88);
            glTranslatef(3.388,-10.782,5.456);
            glRotatef(46.73570459,0,0,1);
            glRotatef(90,1,0,0);
            glScalef(1,1,.12);
            drawsphere(.07,20,20);
        }glPopMatrix();


        glPushMatrix();{
          glColor3f(.88,.88,.88);
            glTranslatef(1.607,-2.695,5.456);
            glRotatef(12.41998751,0,0,1);
            glRotatef(90,1,0,0);
            glScalef(1,1,.41000971);
            drawsphere(.07,20,20);
        }glPopMatrix();



        glPushMatrix();{
          glColor3f(.88,.88,.88);
            glTranslatef(0,0,5.456);
            glRotatef(30.80717685,0,0,1);
            glRotatef(90,1,0,0);
            glScalef(1,1,.15705);
            drawsphere(.07,20,20);
        }glPopMatrix();

        glPushMatrix();{
        glColor3f(.88,.88,.88);
            glTranslatef(0,0,5.456);
            glRotatef(-27.85714393,0,0,1);
            glRotatef(-90,1,0,0);
            glScalef(1,1,.77935);
            drawsphere(.07,20,20);
        }glPopMatrix();
    }glPopMatrix();
}

void Base::drawFilledCircleWithAngle(float x, float y, float radius,float angles, int a){
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	float twicePi = 2.0f * 3.1416* angles;



	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {

            if(a==1){
                A1[i]=x + (radius * cos(i *  twicePi / triangleAmount));
                B1[i]=y + (radius * sin(i * twicePi / triangleAmount));
            }
            else if(a==2){
              A2[i]=x + (radius * cos(i *  twicePi / triangleAmount));
              B2[i]=y + (radius * sin(i * twicePi / triangleAmount));
            }

			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}

void Base::lower(){

    glPushMatrix();{

        glPushMatrix();{
           glTranslatef(-7.387,11.701+5.9325,0);
           glRotatef(-30.829398736,0,0,1);
           glTranslatef(22.34,0,0);
            drawFilledCircleWithAngle(0,0,22.34,.5,1);
        }glPopMatrix();


        glPushMatrix();{
        glBegin(GL_POLYGON);{
            glVertex3f(30.983,-5.286,0);
            glVertex3f(35.983,-20.286,0);
            glVertex3f(30.983,-24.512,0);
            glVertex3f(15.943,-12.82344,0);

        }glEnd();
}glPopMatrix();
glPushMatrix();{
        glBegin(GL_POLYGON);{
            glVertex3f(-7.387,(5.9325+11.701),0);
            glVertex3f(30.983,-5.286,0);
            glVertex3f(-7.387,-24.512,0);
        }glEnd();
        }glPopMatrix();
glPushMatrix();{
        glBegin(GL_POLYGON);{

            glVertex3f(-9.537,6.1665,0);
            glVertex3f(-7.387,5.9325,0);
            glVertex3f(-7.387,(5.9325+11.701),0);
            glVertex3f(-9.537,10.727,0);

        }glEnd();
 }glPopMatrix();
 glPushMatrix();{
        glBegin(GL_POLYGON);{
            glVertex3f(-13.275,6.573,0);
            glVertex3f(-9.537,6.1665,0);
            glVertex3f(-9.537,10.727,0);
            glVertex3f(-12.674,10.437,0);

        }glEnd();
 }glPopMatrix();
 glPushMatrix();{
    glBegin(GL_POLYGON);{
            glVertex3f(-13.275,6.573,0);
            glVertex3f(-19.2194,7.220,0);
            glVertex3f(-19.09,13.489,0);
            glVertex3f(-12.674,10.437,0);
    }glEnd();
    }glPopMatrix();
    }glPopMatrix();
}

void Base::drawLowerSide(){

        glPushMatrix();{



    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,concrete);
    glNormal3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);{
            glTexCoord2f(0,0);glVertex3f(-7.387,5.9325,0);
            glTexCoord2f(0,1);glVertex3f(-7.387,5.9325,-1.183);
            glTexCoord2f(25,1);glVertex3f(-7.387,-24.512,-1.183);
            glTexCoord2f(25,0);glVertex3f(-7.387,-24.512,0);
    }glEnd();



    glBegin(GL_POLYGON);{
            glTexCoord2f(0,0);glVertex3f(30.983,-5.286,0);
            glTexCoord2f(0,1);glVertex3f(30.983,-5.286,-1.183);
            glTexCoord2f(15,1);glVertex3f(35.983,-20.286,-1.183);
            glTexCoord2f(15,0);glVertex3f(35.983,-20.286,0);
    }glEnd();

    glBegin(GL_POLYGON);{
           glTexCoord2f(0,0); glVertex3f(35.983,-20.286,0);
           glTexCoord2f(0,1); glVertex3f(35.983,-20.286,-1.183);
            glTexCoord2f(5,1);glVertex3f(30.983,-24.512,-1.183);
            glTexCoord2f(5,0);glVertex3f(30.983,-24.512,0);
    }glEnd();

    glBegin(GL_POLYGON);{
            glTexCoord2f(0,0);glVertex3f(15.943,-12.82344,0);
            glTexCoord2f(0,1);glVertex3f(15.943,-12.82344,-1.183);
            glTexCoord2f(12,1);glVertex3f(30.983,-24.512,-1.183);
            glTexCoord2f(12,0);glVertex3f(30.983,-24.512,0);

    }glEnd();

    glBegin(GL_POLYGON);{
            glTexCoord2f(0,0);glVertex3f(15.943,-12.82344,0);
            glTexCoord2f(0,1);glVertex3f(15.943,-12.82344,-1.183);
            glTexCoord2f(18,1);glVertex3f(-7.387,-24.512,-1.183);
            glTexCoord2f(18,0);glVertex3f(-7.387,-24.512,0);

    }glEnd();


    glBegin(GL_POLYGON);{
            glTexCoord2f(0,0);glVertex3f(-9.537,10.727,0);
            glTexCoord2f(0,1);glVertex3f(-9.537,10.727,-1.183);
            glTexCoord2f(8,1);glVertex3f(-7.387,11.701+5.9325,-1.183);
            glTexCoord2f(8,0);glVertex3f(-7.387,11.701+5.9325,0);

    }glEnd();

    glBegin(GL_POLYGON);{
            glTexCoord2f(0,0);glVertex3f(-12.674,10.437,0);
            glTexCoord2f(0,1);glVertex3f(-12.674,10.437,-1.183);
            glTexCoord2f(3,1);glVertex3f(-9.537,10.727,-1.183);
            glTexCoord2f(3,0);glVertex3f(-9.537,10.727,0);
    }glEnd();

    glBegin(GL_POLYGON);{
            glTexCoord2f(0,0);glVertex3f(-19.2194,13.489,0);
            glTexCoord2f(0,1);glVertex3f(-19.2194,13.489,-1.183);
            glTexCoord2f(5,1);glVertex3f(-12.674,10.437,-1.183);
            glTexCoord2f(5,0);glVertex3f(-12.674,10.437,0);
    }glEnd();

    glBegin(GL_POLYGON);{
            glTexCoord2f(0,0);glVertex3f(-19.2194,7.220,0);
            glTexCoord2f(0,1);glVertex3f(-19.2194,7.220,-1.183);
            glTexCoord2f(5,1);glVertex3f(-19.094,13.489,-1.183);
            glTexCoord2f(5,0);glVertex3f(-19.094,13.489,0);

    }glEnd();



    glBegin(GL_POLYGON);{
            glTexCoord2f(0,0);glVertex3f(-19.2194,7.220,0);
            glTexCoord2f(0,1);glVertex3f(-19.2194,7.220,-1.183);
            glTexCoord2f(10,1);glVertex3f(-7.387,5.9325,-1.183);
            glTexCoord2f(10,0);glVertex3f(-7.387,5.9325,0);

    }glEnd();

    glDisable(GL_TEXTURE_2D);

        }glPopMatrix();

}

void Base::drawMidSurface(){


    glPushMatrix();{
        glColor3f(1,1,1);
//        glTranslatef(0,0,10);

           glTranslatef(0,14.876,.624);
           glRotatef(-25.64793377,0,0,1);
           glTranslatef(13.71869283,0,0);
        glPushMatrix();{
        for(int j=0;j<20;j++){
        glPushMatrix();{
                glTranslatef(A2[j],B2[j],0);
                glScalef(1,1,.0475);
                drawsphere(.07,20,20);
        }glPopMatrix();
        }
        }glPopMatrix();

    }glPopMatrix();

        glPushMatrix();{
           glTranslatef(0,14.876,0);
           glRotatef(-25.64793377,0,0,1);
           glTranslatef(13.71869283,0,0);
           drawFilledCircleWithAngle(0,0,13.71869283,.5,2);
        }glPopMatrix();

    glPushMatrix();{
        glBegin(GL_POLYGON);{
            glVertex3f(-7.387,5.9325,0);
            glVertex3f(0,14.876,0);
            glVertex3f(24.734,3,0);
            glVertex3f(25.3,1.5,0);
            glVertex3f(24.734,0,0);
            glVertex3f(15.943,-8.791,0);
            glVertex3f(-7.387,-24.512,0);

    }glEnd();
    }glPopMatrix();


    glPushMatrix();{
        glBegin(GL_POLYGON);{

            glVertex3f(-7.387,-24.512,0);
            glVertex3f(15.943,-12.8025,0);
            glVertex3f(15.943,-8.791,0);


    }glEnd();
    }glPopMatrix();
}

void Base::drawMidSurfaceU(){

        //glColor3f(1,1,1);


        glPushMatrix();{
           glTranslatef(0,14.876,0);
           glRotatef(-25.64793377,0,0,1);
           glTranslatef(13.71869283,0,0);
           drawFilledCircleWithAngle(0,0,13.71869283,.5,2);
        }glPopMatrix();

    glPushMatrix();{
        glBegin(GL_POLYGON);{
            glVertex3f(0,14.876,0);
            glVertex3f(-7.387,5.9325,0);
            glVertex3f(-7.387+2,5.1025,0);

    }glEnd();

        glBegin(GL_POLYGON);{
            //glColor3f(1,1,1);
            glVertex3f(0,14.876,0);
            glVertex3f(24.734-.5,3+.5,0);
            glVertex3f(25.3-.5,1.5,0);
            glVertex3f(24.734-.5,0,0);
            glVertex3f(15.943,-8.791,0);
            glVertex3f(-7.387+2,-24.512+1,0);
            glVertex3f(-7.387+2,5.109,0);

    }glEnd();
    }glPopMatrix();


        glPushMatrix();{
        glBegin(GL_POLYGON);{

            glVertex3f(-7.387+2,-23.512,0);
            glVertex3f(15.943,-12.8025,0);
            glVertex3f(15.943,-8.791,0);


    }glEnd();
    }glPopMatrix();

}

void Base::drawAcrStair(){
    float x=-7.387;
    float z=-.624;
    float y1;
    float y2;
    float a1=3.0;
    float a2=1.5;
    float minus=-11.756;


    for(int i=0;i<=4;i++){
        y2=(.5*x)-20.8185-minus;
        y1=(-.414*x)+2.855895;
        a2=a2-minus;
        minus+=2.939;
        if(i!=0){
        glPushMatrix();{
        glPushMatrix();{
        glColor3f(0,.5,0);
        glBegin(GL_QUADS);{
            glVertex3f(x,a1,z);
            glVertex3f(x,y2,z);
            glVertex3f(x-.5,y2,z);
            glVertex3f(x-.5,y1,z);
        }glEnd();
        }glPopMatrix();

        glPushMatrix();{

        glColor3f(1,.5,0);
        glBegin(GL_QUADS);{
            glVertex3f(x-.5,y2,z);
            glVertex3f(x-.5,y2,z-.156);
            glVertex3f(x-.5,y1,z-.156);
            glVertex3f(x-.5,y1,z);
        }glEnd();

          glBegin(GL_QUADS);{
            glVertex3f(x-.5,y2,z);
            glVertex3f(x-.5,y2,z-.156);
            glVertex3f(x,y2,z-.156);
            glVertex3f(x,y2,z);
        }glEnd();

        if(i==4){
        glBegin(GL_QUADS);{
            glVertex3f(-5.387,5.1025,0);
            glVertex3f(-5.387,5.1025,-.156);
            glVertex3f(-5.387,-23.512,-.156);
            glVertex3f(-5.387,-23.512,0);
        }glEnd();
        }

        }glPopMatrix();
        }glPopMatrix();

         z+=.156;
        }
        a1=y1;
        a2=y2;
        x+=.5;

    }
}

void Base::drawStrainghtStair(){
    float x=-7.387;
    float z=-.624;
    float y1;
    float y2;
    float a1=5.9325;
    float a2=-24.512;
    float minus=-11.756;


    for(int i=0;i<=4;i++){
        y2=(.5*x)-20.8185-minus;
        y1=(-.414*x)+2.855895;
        a2=a2-minus;
        minus+=2.939;
        if(i!=0){
            glPushMatrix();{
                glPushMatrix();{
                    //glColor3f(1,1,1);
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D,brickwall);
                        glNormal3f(1.0,0.0,0.0);
                        glBegin(GL_QUADS);{
                            glTexCoord2f(0,0);glVertex3f(x,a1,z);
                            glTexCoord2f(0,1);glVertex3f(x,y2,z);
                            glTexCoord2f(10,1);glVertex3f(x-.5,y2,z);
                            glTexCoord2f(10,0);glVertex3f(x-.5,y1,z);
                        }glEnd();
                        glDisable(GL_TEXTURE_2D);

                }glPopMatrix();

                glPushMatrix();{

                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,midside);
                glNormal3f(1.0,0.0,0.0);
        //glColor3f(1,.5,0);
                glBegin(GL_QUADS);{
                    glTexCoord2f(0,0);glVertex3f(x-.5,y2,z);
                    glTexCoord2f(0,1);glVertex3f(x-.5,y2,z-.156);
                    glTexCoord2f(10,1);glVertex3f(x-.5,y1,z-.156);
                    glTexCoord2f(10,0);glVertex3f(x-.5,y1,z);
                }glEnd();

                glBegin(GL_QUADS);{
                    glTexCoord2f(0,0);glVertex3f(x-.5,y2,z);
                    glTexCoord2f(0,1);glVertex3f(x-.5,y2,z-.156);
                    glTexCoord2f(10,1);glVertex3f(x,y2,z-.156);
                    glTexCoord2f(10,0);glVertex3f(x,y2,z);
                }glEnd();

                if(i==4){
                    glBegin(GL_QUADS);{
                        glTexCoord2f(0,0);glVertex3f(-5.387,5.1025,0);
                        glTexCoord2f(0,1);glVertex3f(-5.387,5.1025,-.156);
                        glTexCoord2f(10,1);glVertex3f(-5.387,-23.512,-.156);
                        glTexCoord2f(10,0);glVertex3f(-5.387,-23.512,0);
                    }glEnd();
                }
                glDisable(GL_TEXTURE_2D);


            }glPopMatrix();

          }glPopMatrix();

          z+=.156;
        }
        a1=y1;
        a2=y2;
        x+=.5;

    }
}

void Base::drawMidSide(){


       glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,midside);
        glNormal3f(1.0,0.0,0.0);

        glBegin(GL_POLYGON);{
            glTexCoord2f(0,0);glVertex3f(-7.387+2,-23.512,0);
            glTexCoord2f(0,1);glVertex3f(-7.387+2,-23.512,-.624);
            glTexCoord2f(7,1);glVertex3f(24.734,0,-.624);
            glTexCoord2f(7,0);glVertex3f(24.734,0,0);

        }glEnd();


        glBegin(GL_POLYGON);{
           glTexCoord2f(0,0); glVertex3f(-7.387,5.9325,0);
            glTexCoord2f(0,1);glVertex3f(-7.387,5.9325,-.624);
            glTexCoord2f(7,1);glVertex3f(0,14.876,-.624);
            glTexCoord2f(7,0);glVertex3f(0,14.876,0);

        }glEnd();

        glBegin(GL_POLYGON);{
            glTexCoord2f(0,0);glVertex3f(-7.387,5.9325,0);
            glTexCoord2f(0,1);glVertex3f(-7.387,5.9325,-.624);
            glTexCoord2f(7,1);glVertex3f(-7.387+2,5.1025,-.624);
            glTexCoord2f(7,0);glVertex3f(-7.387+2,5.1025,0);

    }glEnd();

        glBegin(GL_POLYGON);{
           glTexCoord2f(0,0);glVertex3f(-7.387+2,-23.512,0);
            glTexCoord2f(0,1);glVertex3f(-7.387+2,-23.512,-.624);
            glTexCoord2f(7,1);glVertex3f(15.943,-12.8025,-.624);
            glTexCoord2f(7,0);glVertex3f(15.943,-12.8025,0);

    }glEnd();

   glDisable(GL_TEXTURE_2D);

}

void Base::drawArcTorus(){

    glPushMatrix();{
       glPushMatrix();{
            glTranslatef(10+5,13,4.0)   ;
            glRotatef(-90,1,0,0);
            glScalef(1,1,.15);
            drawsphere(.25,20,20);
       }glPopMatrix();

       glPushMatrix();{
        glTranslatef(10,13,4.0)   ;
        glRotatef(-90,1,0,0);
        glScalef(1,1,.15);
        drawsphere(.25,20,20);
       }glPopMatrix();

        glPushMatrix();{
            glTranslatef(7.284,13.0,4.0)   ;
            glRotatef(-90,0,1,0);
            glScalef(1,1,.12);
            drawsphere(.25,20,20);
       }glPopMatrix();

        glPushMatrix();{
            glTranslatef(12.566,0,0);
            glTranslatef(7.284,13.0,4.0)   ;
            glRotatef(-90,0,1,0);
            glScalef(1,1,.12);
            drawsphere(.25,20,20);
       }glPopMatrix();

        glPushMatrix();{
            glTranslatef(5.284,10.0,4.0)   ;
            glRotatef(-90,0,1,0);
            glScalef(1,1,.17);
            drawsphere(.25,20,20);
       }glPopMatrix();

        glPushMatrix();{
            glTranslatef(17,0,0);
            glTranslatef(5.284,10.0,4.0)   ;
            glRotatef(-90,0,1,0);
            glScalef(1,1,.17);
            drawsphere(.25,20,20);
       }glPopMatrix();

        glPushMatrix();{
            glTranslatef(4.284,7.0,4.0)   ;
            glRotatef(-90,0,1,0);
            glScalef(1,1,.16);
            drawsphere(.25,20,20);
       }glPopMatrix();

        glPushMatrix();{
            glTranslatef(19,0,0);
            glTranslatef(4.284,7.0,4.0)   ;
            glRotatef(-90,0,1,0);
            glScalef(1,1,.16);
            drawsphere(.25,20,20);
       }glPopMatrix();

        glPushMatrix();{
            glTranslatef(3.284,6.5,4.0)   ;
            glRotatef(40,0,0,1);
            glRotatef(-90,0,1,0);
            glScalef(1,1,.16);
            drawsphere(.25,20,20);
       }glPopMatrix();

        glPushMatrix();{
            glTranslatef(18.5,0,0);
            glTranslatef(3.284,6.5,4.0)   ;
            glRotatef(90+40,0,0,1);
            glRotatef(-90,0,1,0);
            glScalef(1,1,.17);
            drawsphere(.25,20,20);
       }glPopMatrix();

       glPushMatrix();{
        glTranslatef(12.367,5,4.0);
        glutSolidTorus(0.3, 11.367, 10, 50);
       }glPopMatrix();


    }glPopMatrix();


}

void Base::drawCurveRod(){
           /*glTranslatef(0,14.876,0);
           glRotatef(-25.64793377,0,0,1);
           glTranslatef(13.71869283,0,0);*/


    // glTranslatef(0,14.876,0);
	//glTranslatef(13.71869283,0,0);

	glTranslatef(13.71869283*cos(25.64793377)+.5,14.876-(13.71869283*cos(25.64793377))+5.9,0);
	glRotatef(-25.64793377,0,0,1);
    //glTranslatef(-13.71869283,0,0);
    double coef[4];
	coef[0] = 0;	//-1.x
	coef[1] = 1;	//0.y
	coef[2] = 0;	//0.z
	coef[3] = 0;	//10
	//standard format:: ax + by + cz + d >= 0

	//		x <= 10
	//OR	-1.x + 0.y + 1.z + 10 >= 0
	glClipPlane(GL_CLIP_PLANE0,coef);
	//now we enable the clip plane
	glEnable(GL_CLIP_PLANE0);{
            glutSolidTorus(.09,13.71869283,20,40);
	}glDisable(GL_CLIP_PLANE0);

}

void Base::drawMidGril(){

    glPushMatrix();{

            glTranslatef(-7.387,5.9325,.950);
            glRotatef(-39.55544596,0,0,1);
            glRotatef(-90,1,0,0);
            glScalef(1,1,.579986985);
            drawsphere(.07,20,20);

    }glPopMatrix();

    float x=-7.387;
    for(int i=0;i<11;i++){
            float y=((x+7.387)*(5.9325-14.876)/(-7.387-0))+5.9325;
            glPushMatrix();{
                glTranslatef(x,y,0);
                glScalef(1,1,.0475);
                drawsphere(.07,20,20);
            }glPopMatrix();
            x+=.7387;
    }

    glPushMatrix();{

        glTranslatef(0,0,.95);
        drawCurveRod();
    }glPopMatrix();

}

void Base::drawBase(){
    glPushMatrix();{


    glPushMatrix();{
        glColor3f(1,1,1);
        drawArcTorus();

    }glPopMatrix();

    glPushMatrix();{
        glColor3f(1,1,1);
        drawStrainghtStair();
    }glPopMatrix();


    glPushMatrix();{
        glColor3f(1,1,1);
        drawMidSide();
    }glPopMatrix();

    glPushMatrix();{
        glColor3f(.88,.88,.88);
        drawMidGril();
    }glPopMatrix();

    glPushMatrix();{

        glColor3f(95.0/255.0,158.0/255.0,160.0/255.0);
        //glColor3f(.75,0,.75);
        drawMidSurfaceU();
    }glPopMatrix();

    glPushMatrix();{

        glColor3f(205.0/255.0,190.0/255.0,112.0/255.0);
        //glColor3f(.75,.75,.75);
        glTranslatef(0,0,-.624);
        drawMidSurface();
    }glPopMatrix();

    glPushMatrix();{

        glTranslatef(0,0,-.624);
        glPushMatrix();{
            glColor3f(1,1,1);
            drawLowerSide();
        }glPopMatrix();



        glPushMatrix();{

            //glColor3f(1,1,1);
            glColor3f(.545098039,.505882352,.298039215);
            lower();
            glTranslatef(0,0,-1.183);
            lower();
        }glPopMatrix();

    }glPopMatrix();


    glPushMatrix();{
        glColor3f(.88,.88,.88);
        glTranslatef(0,0,4.506);
        glPushMatrix();{
        drawHorizontalGrill();
        glTranslatef(12.367,0,.9);
        glRotatef(180,0,1,0);
        glTranslatef(-12.367,0,0);
        drawHorizontalGrill();
        }glPopMatrix();
    }glPopMatrix();


    glPushMatrix();{
        glColor3f(.88,.88,.88);
        drawGrill();
        glTranslatef(12.367,0,5.456);
        glRotatef(180,0,1,0);
        glTranslatef(-12.367,0,-5.456);
        drawGrill();
    }glPopMatrix();

    glPushMatrix();{
        drawSide(0);
        glTranslatef(12.367,0,4.506);
        glRotatef(180,0,1,0);
        glTranslatef(-12.367,0,0);
        drawSide(1);
    }glPopMatrix();

    glPushMatrix();{
          glTranslatef(12,-6,0)    ;
          glRotatef(-130,0,0,1);
          drawFilledCirclewithSide();
    }glPopMatrix();

    glPushMatrix();{
        glColor3f(1,1,1);
        drawSurface();
        glTranslatef(0,0,4.506);
        drawSurface();
    }glPopMatrix();



    }glPopMatrix();

}

void Base::base(){

    drawBase();

	glPushMatrix();{
        glPushMatrix();{
			glTranslatef(18.5,-1,10.6);
			glScalef(1.5,1.5,1.5);
			glRotatef(180,0,0,1);
        glPushMatrix();{
          glTranslatef(0,14.876,-4.506);
          glRotatef(-25.64793377,0,0,1);
          glTranslatef(13.71869283,0,0);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,midside);
        glNormal3f(1.0,0.0,0.0);
        for(int k=0;k<19;k++){
            glPushMatrix();{
                glBegin(GL_QUADS);{
                  glTexCoord2f(0,0);glVertex3f(A2[k],B2[k],0);
                  glTexCoord2f(0,1);glVertex3f(A2[k],B2[k],-.624);
                  glTexCoord2f(1,1);glVertex3f(A2[k+1],B2[k+1],-.624);
                  glTexCoord2f(1,0);glVertex3f(A2[k+1],B2[k+1],0);
                }glEnd();

            }glPopMatrix();
        }
        glDisable(GL_TEXTURE_2D);

        }glEnd();
        }glPopMatrix();

        glPushMatrix();{
      //  glColor3f(1,1,0);

        glPopMatrix();{

           glTranslatef(-7.387,11.701+5.9325,-(4.506+.624));
           glRotatef(-30.829398736,0,0,1);
           glTranslatef(22.34,0,0);


        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,concrete);
        glNormal3f(1.0,0.0,0.0);
        for(int k=0;k<19;k++){
            glPushMatrix();{
                glBegin(GL_QUADS);{
                  glTexCoord2f(0,0);glVertex3f(A1[k],B1[k],0);
                  glTexCoord2f(0,1);glVertex3f(A1[k],B1[k],-1.183);
                  glTexCoord2f(3,1);glVertex3f(A1[k+1],B1[k+1],-1.183);
                  glTexCoord2f(3,0);glVertex3f(A1[k+1],B1[k+1],0);
                }glEnd();

            }glPopMatrix();
        }

         glDisable(GL_TEXTURE_2D);

        }glEnd();
        }glPopMatrix();
}glPopMatrix();
}

int num_texture = -1;
static int LoadBitmap(char *filename)
{
    int i, j=0;
    FILE *l_file;
    unsigned char *l_texture;

    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    num_texture++;

    if( (l_file = fopen(filename, "rb"))==NULL) return (-1);

    fread(&fileheader, sizeof(fileheader), 1, l_file);

    fseek(l_file, sizeof(fileheader), SEEK_SET);
    fread(&infoheader, sizeof(infoheader), 1, l_file);

    l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
 for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
    {
            fread(&rgb, sizeof(rgb), 1, l_file);

            l_texture[j+0] = rgb.rgbtRed;
            l_texture[j+1] = rgb.rgbtGreen;
            l_texture[j+2] = rgb.rgbtBlue;
            l_texture[j+3] = 255;
            j += 4;
    }
    fclose(l_file);

    glBindTexture(GL_TEXTURE_2D, num_texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
     gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture);

    return (num_texture);

}


void Base::initialize(){
	IQuadric=gluNewQuadric();
   
	texid =LoadBitmap("textures/Spinnaker_Tower.bmp");
    upside1=LoadBitmap("textures/upperside1.bmp");
    upside2=LoadBitmap("textures/upperside2.bmp");
    upside3=LoadBitmap("textures/upperside3.bmp");
    upside4=LoadBitmap("textures/upperside4.bmp");
    upsideR1=LoadBitmap("textures/upperside1Reverse.bmp");
    upsideR2=LoadBitmap("textures/upperside2Reverse.bmp");
    upsideR3=LoadBitmap("textures/upperside3Reverse.bmp");
    upsideR4=LoadBitmap("textures/upperside4Reverse.bmp");
    midside=LoadBitmap("textures/Fencing_Weathered.bmp");
    brickwall=LoadBitmap("textures/brickwall.bmp");
    concrete=LoadBitmap("textures/concrete.bmp");
    door=LoadBitmap("textures/door.bmp");
}