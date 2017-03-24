#include "stdafx.h"
#include "Vectors.h"


Vectors::Vectors(){

}

Vectors::Vectors(double a,double b,double c){

	x=a;
	y=b;
	z=c;
}

double Vectors::getX(){
    return x;
}

double Vectors::getY(){
    return y;
}

double Vectors::getZ(){
    return z;
}

