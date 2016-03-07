#include "ball.h"

//#include "foundation.h"

// Constructor
Ball::Ball()
{
    radius = 100.0f;
    origin = vec3(-2.0f*radius, 405.0f, 0.0f);
}

// Destructor
Ball::~Ball()
{

}

// Draw function
void Ball::draw()
{
    // get the coordinates and radius
    float x = origin.x;
    float y = origin.y;
    float z = origin.z;
    float resolution = 20.0f;

    // Compute angle of each triangle in fan
    float theta = 2.0f * PI / resolution;

    glColor3f(0.1,0.3,0.6);
    /*glBegin(GL_TRIANGLE_FAN);

        glVertex3f(x, y, z);  // centre point
        for( int i=0; i<=resolution; i++ )
        {
            // Apply the Pythagorean Theorem to get next point
            glVertex3f(
                x + radius * sin( i * theta ),
                y + radius * cos( i * theta ),
                        z
            );
        }
    glEnd();

    /* draw 3d sphere */
    int numSlices = 32;
    int numStacks = 8;

    GLUquadricObj* pQuadric = gluNewQuadric();  // make the quadric
    assert(pQuadric!=NULL); // make sure the quadric exists*/
    //glPushMatrix(); // draw and place Sphere
    glTranslatef(origin.x, origin.y, origin.z); // move sphere to ball's origin
    gluSphere(pQuadric,radius,numSlices,numStacks); // draw the spphere

    /*glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/
    //solidSphere(radius,numSlices,numStacks);
    //glutSolidSphere(radius,numSlices,numStacks);
    //glPopMatrix();
    //glutSwapBuffers();

    /* Add lighting */
    vec4 fColor = vec4(0.2, 0.2, 1, 1);
    //vec3 fpoint = (vec3)fColor;   // eye position
    vec3 fpoint = vec3(origin.x, origin.y, origin.z+1);
    //lighting
    vec3 L = vec3(100,100,1); //lightsource
    float intensity = 1.0;

    float light = intensity*glm::max(0.0f, dot(normalize(fpoint), normalize(L)));
    fColor += light;

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


// tetrahedron
//tetrahedron
