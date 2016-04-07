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
    /*int numSlices = 32;
    int numStacks = 8;

    GLUquadricObj* pQuadric = gluNewQuadric();  // make the quadric
    assert(pQuadric!=NULL); // make sure the quadric exists
    glTranslatef(origin.x, origin.y, origin.z); // move sphere to ball's origin
    gluSphere(pQuadric,radius,numSlices,numStacks); // draw the sphere*/


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

// Check for collision of one particle with ball
bool Ball::collidesWith(Particle * p, int number)
{
    // find distance from ball's origin
    vec3 distanceVector;
    switch(number){
    case 0:
        distanceVector = p->position - origin;
        break;
    case 1:
        distanceVector = p->position1 - origin;
        break;
    case 2:
        distanceVector = p->position2 - origin;
        break;
    default://case 3:
        distanceVector = p->position3 - origin;
        //break;
    }

    float distance = length(distanceVector);

    if( distance < radius * 1.1f )  // <=
    {
        // push particle back to ball's circumference
        /*vec3 x = origin + normalize(distanceVector) * radius * 1.1f;

        switch(number){
        case 0:
            p->position = x;
            break;
        case 1:
            p->position1 = x;
            break;
        case 2:
            p->position2 = x;
            break;
        default:    // case 3:
            p->position3 = x;
        }*/

        // collision detected
        return true;
    }

    // no collision detected
    return false;
}


//========TEXTURES================================================
void Ball::drawTextures(GLuint texture)
{
    /*glMatrixMode(GL_TEXTURE);

    GLfloat planes[] = {0.5, 0.0, 0.0, 0.5}; // s = x/2 + 1/2
    GLfloat planet[] = {0.0, 0.5, 0.0, 0.5}; // t = y/2 + 1/2
    //GLfloat depth[] =  {0.0, 0.0, 0.5, 0.5}; // r = z/2 + 1/2 ?

    GLfloat zPlane[] = { 0.0f, 0.0f, 1.0f, 0.0f };

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);    // ?
    glTexGenfv(GL_S, GL_SPHERE_MAP, planes);
    glTexGenfv(GL_T, GL_SPHERE_MAP, planet);
    glTexGenfv(GL_R, GL_SPHERE_MAP, zPlane);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);*/

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(origin.x, origin.y, origin.z);
    glShadeModel( GL_SMOOTH );
        glEnable(GL_DEPTH_TEST);
        //glEnable(GL_TEXTURE_2D);
        glColor3f(1, 1, 1);
        //glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_TRIANGLES);
            int numSlices = 32;
            int numStacks = 32;
            GLUquadricObj* pQuadric = gluNewQuadric();  // make the quadric
            assert(pQuadric!=NULL); // make sure the quadric exists
            gluSphere(pQuadric,radius,numSlices,numStacks); // draw the sphere
        glEnd();
        glPopMatrix();
        //glDisable(GL_TEXTURE_2D);

    //glLoadIdentity();
    //glMatrixMode(GL_MODELVIEW);
}
