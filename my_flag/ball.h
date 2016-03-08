#ifndef BALL_H
#define BALL_H

#include "foundation.h"

class Ball
{
public:
    Ball(int zCentre);
    ~Ball();

    float radius;
    vec3 origin;

    void draw();

    void solidSphere(GLdouble radius, GLint slices, GLint stacks);
};

#endif // BALL_H
