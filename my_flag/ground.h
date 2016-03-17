#ifndef GROUND_H
#define GROUND_H

#include "foundation.h"

class Ground
{
public:
    Ground(int height);
    ~Ground();

    draw();

    void initializeShader();

    // parameters for collision detection
    float y;    // Height
    float xmin;
    float xmax;
    float zmin;
    float zmax;

private:
    static const int width = 256;  // length of a side of the square ground

    //=====Texture mapping======================
    /*GLuint texBufferID;
    GLuint texCoordID, texID;

    GLubyte image[width][width][3];
    GLfloat * uvs;*/

    //=====Shader Stuff===================
    GLuint texBufferID;
    GLuint texCoordID, texID;

    void LoadGLTextures(const char * name);

    void testTextures();
    //====================================

    //==========================================
};

#endif // GROUND_H
