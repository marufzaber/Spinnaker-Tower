#include "stdafx.h"
#include "Cameras.h"

Cameras::Cameras(){

}

Cameras::Cameras(Vectors f,Vectors u,Vectors r){
	front = f;
	up = u;
	right = r;
}

Vectors Cameras::LookAtPosition(){

    Vectors myobj(front.getX()*30,front.getY()*30,front.getZ()*30);
    Vectors myobj1(position.getX()+myobj.getX(),position.getY()+myobj.getY(),position.getZ()+myobj.getZ());
	return myobj1;
}

//move forward or backward with magnitude 'value'
void Cameras::Move(Vectors dir, double val)
{
    Vectors myobj(dir.getX()*val,dir.getY()*val,dir.getZ()*val);
    Vectors myobj1(position.getX()+myobj.getX(),position.getY()+myobj.getY(),position.getZ()+myobj.getZ());
	position = myobj1;
}

//pitch up or down 'angle' degrees
void Cameras::Pitch(double angle)
{
	double radian = 2*angle*acos(0.)/180;
	Vectors myobj(front.getX()*sin(radian),front.getY()*sin(radian),front.getZ()*sin(radian));
    Vectors myobj1(up.getX()*cos(radian),up.getY()*cos(radian),up.getZ()*cos(radian));
    Vectors myobj2(myobj.getX()+myobj1.getX(),myobj.getY()+myobj1.getY(),myobj.getZ()+myobj1.getZ());
	up = myobj2;

	Vectors myobj3(front.getX()*cos(radian),front.getY()*cos(radian),front.getZ()*cos(radian));
    Vectors myobj4(up.getX()*-1,up.getY()*-1,up.getZ()*-1);
    Vectors myobj5(myobj4.getX()*sin(radian),myobj4.getY()*sin(radian),myobj4.getZ()*sin(radian));
    Vectors myobj6(myobj3.getX()+myobj5.getX(),myobj3.getY()+myobj5.getY(),myobj3.getZ()+myobj5.getZ());

	front = myobj6;
}

//turn left or right 'angle' degrees
void Cameras::Turn(double angle)
{
	double radian = 2*angle*acos(0.)/180;

    Vectors myobj(right.getX()*sin(radian),right.getY()*sin(radian),right.getZ()*sin(radian));
    Vectors myobj1(front.getX()*cos(radian),front.getY()*cos(radian),front.getZ()*cos(radian));
    Vectors myobj2(myobj.getX()+myobj1.getX(),myobj.getY()+myobj1.getY(),myobj.getZ()+myobj1.getZ());
    front=myobj2;


    Vectors myobj3(front.getX()*-1,front.getY()*-1,front.getZ()*-1);
    Vectors myobj4(myobj3.getX()*sin(radian),myobj3.getY()*sin(radian),myobj3.getZ()*sin(radian));
    Vectors myobj5(right.getX()*cos(radian),right.getY()*cos(radian),right.getZ()*cos(radian));
    Vectors myobj6(myobj4.getX()+myobj5.getX(),myobj4.getY()+myobj5.getY(),myobj4.getZ()+myobj5.getZ());

	right = myobj6;
}

//roll left or right 'angle' degrees
void Cameras::Roll(double angle)
{
	double radian = 2*angle*acos(0.)/180;

	Vectors myobj(up.getX()*cos(radian),up.getY()*cos(radian),up.getZ()*cos(radian));
	Vectors myobj1(right.getX()*sin(radian),right.getY()*sin(radian),right.getZ()*sin(radian));
	Vectors myobj2(myobj.getX()+myobj1.getX(),myobj.getY()+myobj1.getY(),myobj.getZ()+myobj1.getZ());
	up=myobj2;

    Vectors myobj3(up.getX()*-1,up.getY()*-1,up.getZ()*-1);
    Vectors myobj4(myobj3.getX()*sin(radian),myobj3.getY()*sin(radian),myobj3.getZ()*sin(radian));
    Vectors myobj5(right.getX()*cos(radian),right.getY()*cos(radian),right.getZ()*cos(radian));
    Vectors myobj6(myobj4.getX()+myobj5.getX(),myobj4.getY()+myobj5.getY(),myobj4.getZ()+myobj5.getZ());

	right = myobj6;
}

Vectors Cameras::getFront(){
    return front;
}

Vectors Cameras::getUp(){
    return up;
}

Vectors Cameras::getRight(){
    return right;
}

Vectors Cameras::getPosition(){
    return position;
}
