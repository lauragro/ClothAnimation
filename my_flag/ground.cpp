#include "ground.h"

// Constructor
Ground::Ground(int height)
{
    y = float(height);
}

// Destructor
Ground::~Ground()
{

}

// Draw function
Ground::draw(GLuint texture)
{
    xmin = -256.0f;
    zmin = xmin;
    xmax = 256.0f;
    zmax = xmax;

    /* draw the lines */
    //drawFixedGround(width, y);

    /* Make the grass */
    drawTextures(texture);

}

//========TEXTURES================================================
void Ground::drawTextures(GLuint texture)
{
    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glShadeModel( GL_SMOOTH );
        glEnable(GL_TEXTURE_2D);
        glColor3f(0.5, 0.5, 0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, y, zmax);  // vertex 1
            glTexCoord2f(0.0f, 0.0f); glVertex3f(xmin, y, zmin); // vertex 2
            glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, y, zmin);  // vertex 3
            glTexCoord2f(1.0f, 1.0f); glVertex3f(xmax, y, zmax);   // vertex 4
        glEnd();
        glDisable(GL_TEXTURE_2D);
}


// draw a fixed vertex ground
/*void drawFixedGround(int width, float y)
{
    glBegin(GL_LINES);
        for( int i=0; i<width/2; i+=10)
        {
            // back line
            glVertex3f(-width/2+i, y, -width/2+i);
            glVertex3f(width/2-i, y, -width/2+i);

            // right line
            glVertex3f(width/2-i, y, -width/2+i);
            glVertex3f(width/2-i, y, width/2-i);

            // front line
            glVertex3f(width/2-i, y, width/2-i);
            glVertex3f(-width/2+i, y, width/2-i);

            // left line
            glVertex3f(-width/2+i, y, width/2-i);
            glVertex3f(-width/2+i, y, -width/2+i);
        }
    glEnd();
}*/
