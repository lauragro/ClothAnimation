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
    int y = 100;

    // avoid attaching ground to ball
    glPushMatrix();

    glColor3f(0.5,0.5,0.5);

    glBegin(GL_LINES);
        //for(int i=0; i<= width; i+=10)
        //for(int i=-width/2; i<=width/2; i+=10)
        for( int i=0; i<width/2; i+=10)
        {
            // back line
            //glVertex3f(i, y, -i);
            //glVertex3f(width/2-i, y, -i);
            glVertex3f(-width/2+i, y, -width/2+i);
            glVertex3f(width/2-i, y, -width/2+i);

            // right line
            //glVertex3f(width/2-i, y, -i);
            //glVertex3f(width/2-i, y, -(width/2-i));
            glVertex3f(width/2-i, y, -width/2+i);
            glVertex3f(width/2-i, y, width/2-i);

            // front line
            //glVertex3f(width/2-i, y, -(width/2-i));
            //glVertex3f(i, y, -(width/2-i));
            glVertex3f(width/2-i, y, width/2-i);
            glVertex3f(-width/2+i, y, width/2-i);

            // left line
            //glVertex3f(i, y, -(width/2-i));
            //glVertex3f(i, y, -i);
            glVertex3f(-width/2+i, y, width/2-i);
            glVertex3f(-width/2+i, y, -width/2+i);
        }
    glEnd();
    glPopMatrix();
}
