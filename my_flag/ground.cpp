#include "ground.h"

// Constructor
Ground::Ground(int width)
{
    this->width = width;
}

// Destructor
Ground::~Ground()
{

}

// Draw function
Ground::draw()
{
    // set the verticle position of the ground
    int y = 500;

    // avoid attaching ground to ball
    glPushMatrix();

    glColor3f(0.5,0.5,0.5);

    glBegin(GL_LINES);
        for(int i=0; i<= width; i+=10)
        {
            // back line
            glVertex3f(i, y, i);
            glVertex3f(width-i, y, i);

            // right line
            glVertex3f(width-i, y, i);
            glVertex3f(width-i, y, width-i);

            // front line
            glVertex3f(width-i, y, width-i);
            glVertex3f(i, y, width-i);

            // left line
            glVertex3f(i, y, width-i);
            glVertex3f(i, y, i);
        }
    glEnd();
    glPopMatrix();
}
