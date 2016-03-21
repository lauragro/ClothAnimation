#include "ball.h"

// Constructor
Ball::Ball(int zCentre)
{
    radius = 100.0f;
    origin = vec3(0,0,zCentre);
}

// Destructor
Ball::~Ball()
{

}

// Draw function
void Ball::draw(GLuint texture)
{

    glMatrixMode(GL_MODELVIEW);

    // get the coordinates and radius
    float x = origin.x;
    float y = origin.y;
    float z = origin.z;
    float resolution = 20.0f;

    // Compute angle of each triangle in fan
    float theta = 2.0f * PI / resolution;

    glColor3f(0.1,0.3,0.6);

    /* draw 3d sphere */
    int numSlices = 32;
    int numStacks = 8;

    GLUquadricObj* pQuadric = gluNewQuadric();  // make the quadric
    assert(pQuadric!=NULL); // make sure the quadric exists
    glTranslatef(origin.x, origin.y, origin.z); // move sphere to ball's origin
    gluSphere(pQuadric,radius,numSlices,numStacks); // draw the sphere


    drawTextures(texture);

}

// draw a solid sphere
void Ball::solidSphere(GLdouble radius, GLint slices, GLint stacks)
{
    glPushMatrix(); // remember current matrix
    glTranslatef(origin.x, origin.y, origin.z); // move to ball's origin

    glBegin(GL_LINE_LOOP);
        GLUquadricObj* quadric = gluNewQuadric();
        assert(quadric!=NULL); // make sure the quadric exists
        gluQuadricDrawStyle(quadric, GLU_FILL);
        gluSphere(quadric, radius, slices, stacks);
        gluDeleteQuadric(quadric);
    glEnd();

    glPopMatrix();  // restore old matrix
}


//========TEXTURES================================================
void Ball::drawTextures(GLuint texture)
{
    glMatrixMode(GL_MODELVIEW);

    glShadeModel( GL_SMOOTH );
        glEnable(GL_SPHERE_MAP);
        glColor3f(1, 1, 1);
        glBindTexture(GL_SPHERE_MAP, texture);

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-200, 100, 0);  // vertex 1
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-200, 100, -200); // vertex 2
            glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 100, -200);  // vertex 3
            glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 100, 0);   // vertex 4

            /*int numSlices = 32;
            int numStacks = 8;

            GLUquadricObj* pQuadric = gluNewQuadric();  // make the quadric
            assert(pQuadric!=NULL); // make sure the quadric exists
            glTranslatef(origin.x, origin.y, origin.z); // move sphere to ball's origin
            gluSphere(pQuadric,radius,numSlices,numStacks); // draw the sphere*/


        glEnd();
        glDisable(GL_SPHERE_MAP);
}
