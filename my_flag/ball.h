#ifndef BALL_H
#define BALL_H

#include "vector3d.h"

class Ball
{
public:
    Ball();
    ~Ball();

    double radius;      // radius of ball
    Vector3D origin;    // (x,y,z) coordinates of ball
};

#endif // BALL_H
