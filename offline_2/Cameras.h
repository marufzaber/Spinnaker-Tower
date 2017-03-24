#pragma once

#include "Vectors.h"
#include <math.h>

class Cameras
{
public:

    Vectors front;
    Vectors up;
    Vectors right;
    Vectors position;
    Cameras();
    Cameras(Vectors F, Vectors U, Vectors R);
    Vectors LookAtPosition();
    void Move(Vectors dir, double value);
    void Pitch(double angle);
    void Turn(double angle);
    void Roll(double angle);
    Vectors getFront();
    Vectors getUp();
    Vectors getRight();
    Vectors getPosition();

};

