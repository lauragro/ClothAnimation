#ifndef GROUND_H
#define GROUND_H

#include "foundation.h"

class Ground
{
public:
    Ground(int height);
    ~Ground();

    draw(GLuint texture);

    void initializeShader();

    // parameters for collision detection
    float y;    // Height
    float xmin;
    float xmax;
    float zmin;
    float zmax;
    float ymax;
    float ymin;

private:
    static const int width = 256;  // length of a side of the square ground

    //=====Shader Stuff===================
    void drawTextures(GLuint texture);
    //====================================

    // todo: fix this
    //void drawFixedGround(int width, float y);
    //==========================================
};

#endif // GROUND_H
