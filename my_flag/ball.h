#ifndef BALL_H
#define BALL_H

#include "foundation.h"

class Ball
{
public:
    Ball();
    ~Ball();

    float radius;
    vec3 origin;

    void draw();
};

#endif // BALL_H
