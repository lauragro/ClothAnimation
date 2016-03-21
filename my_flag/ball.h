#ifndef BALL_H
#define BALL_H

#include "foundation.h"

class Ball
{
public:
    Ball(int zCentre);
    ~Ball();

    void initializeShader();

    float radius;
    vec3 origin;

    void draw(GLuint texture);

    void solidSphere(GLdouble radius, GLint slices, GLint stacks);

private:
    //=====Shader Stuff===================
    void drawTextures(GLuint texture);
    //====================================

};

#endif // BALL_H
