#ifndef GROUND_H
#define GROUND_H

#include "foundation.h"

class Ground
{
public:
    Ground(int width);
    ~Ground();

    draw();

    void initializeShader();

    // height of ground
    float y;

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
