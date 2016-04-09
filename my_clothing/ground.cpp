#include "ground.h"

// Constructor
Ground::Ground(int height)
{
    y = float(height);

    coefficientOfFriction = 10.0f;   // TODO: experiment to find a good one

    xmin = -1024.0f;//-256.0f;
    zmin = xmin;
    xmax = 1024.0f;//256.0f;
    zmax = xmax;
    ymin = y;
    ymax = ymin + 64.0f;

    // normal vectors
    bottomNormal = vec3(0.0f, 1.0f, 0.0f);
    frontNormal = vec3(0.0f, 0.0f, 1.0f);
    rightNormal = vec3(1.0f, 0.0f, 0.0f);
    topNormal = -1.0f * bottomNormal;
    leftNormal = -1.0f * rightNormal;
    backNormal = -1.0f * frontNormal;

    /*bottomNormal = normalize(cross(vec3(xmin-xmax, 0.0f, zmin-zmax), vec3(xmin-xmax, 0.0f, zmax-zmin)));
    frontNormal = normalize(cross(vec3(xmin-xmax, ymin-ymax, 0.0f), vec3(xmin-xmax, ymax-ymin, 0.0f)));
    rightNormal = normalize(cross(vec3(0.0f, ymin-ymax, zmin-zmax), vec3(0.0f, ymin-ymax, zmax-zmin)));
    topNormal = -1.0f * bottomNormal;
    leftNormal = -1.0f * rightNormal;
    backNormal = -1.0f * frontNormal;*/
}

// Destructor
Ground::~Ground()
{

}

// Draw function
Ground::draw(GLuint texture)
{


    /* draw the lines */
    //drawFixedGround(width, y);

    /* Make the grass */
    drawTextures(texture);

}

bool Ground::collidesWith(Particle *p)
{
    // particle coords
    float x,y,z;
        x = p->position.x;
        y = p->position.y;
        z = p->position.z;


    // ground coords
    //float ymin = myGround->ymin;
    /*float ymax = myGround->ymax;
    float xmin = myGround->xmin;
    float xmax = myGround->xmax;
    float zmin = myGround->zmin;
    float zmax = myGround->zmax;*/

    // collides with block
    if(     y >= ymin-5.0f
         /*&& y <= ymax
         && x >= xmin
         && x <= xmax
         && z >= zmin
         && z <= zmax */  )
    {
        // push particle back
        p->position.y = ymin- 6.0f;

        // collision detected
        return true;
    }

    // no collision detected
    return false;
}

//========TEXTURES================================================
void Ground::drawTextures(GLuint texture)
{
    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glShadeModel( GL_SMOOTH );
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
        glColor3f(0.5, 0.5, 0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // TOP
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, ymin, zmax);  // vertex 1
            glTexCoord2f(0.0f, 0.0f); glVertex3f(xmin, ymin, zmin); // vertex 2
            glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, ymin, zmin);  // vertex 3
            glTexCoord2f(1.0f, 1.0f); glVertex3f(xmax, ymin, zmax);   // vertex 4
        glEnd();

        // FRONT
        /*glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, ymin, zmax);  // vertex 1
            glTexCoord2f(0.0f, 0.0f); glVertex3f(xmax, ymin, zmax); // vertex 2
            glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, ymax, zmax);  // vertex 3
            glTexCoord2f(1.0f, 1.0f); glVertex3f(xmin, ymax, zmax);   // vertex 4
        glEnd();

        // RIGHT
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(xmax, ymax, zmax);  // vertex 1
            glTexCoord2f(0.0f, 0.0f); glVertex3f(xmax, ymin, zmax); // vertex 2
            glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, ymin, zmin);  // vertex 3
            glTexCoord2f(1.0f, 1.0f); glVertex3f(xmax, ymax, zmin);   // vertex 4
        glEnd();

        // BACK
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, ymax, zmin);  // vertex 1
            glTexCoord2f(0.0f, 0.0f); glVertex3f(xmax, ymax, zmin); // vertex 2
            glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, ymin, zmin);  // vertex 3
            glTexCoord2f(1.0f, 1.0f); glVertex3f(xmin, ymin, zmin);   // vertex 4
        glEnd();

        // LEFT
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, ymax, zmax);  // vertex 1
            glTexCoord2f(0.0f, 0.0f); glVertex3f(xmin, ymax, zmin); // vertex 2
            glTexCoord2f(1.0f, 0.0f); glVertex3f(xmin, ymin, zmin);  // vertex 3
            glTexCoord2f(1.0f, 1.0f); glVertex3f(xmin, ymin, zmax);   // vertex 4
        glEnd();*/

        // BOTTOM
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, ymin, zmin);  // vertex 1
            glTexCoord2f(0.0f, 0.0f); glVertex3f(xmin, ymin, zmax); // vertex 2
            glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, ymin, zmax);  // vertex 3
            glTexCoord2f(1.0f, 1.0f); glVertex3f(xmax, ymin, zmin);   // vertex 4
        glEnd();

        glDisable(GL_TEXTURE_2D);
}


// draw a fixed vertex ground
void Ground::drawFixedGround()
{
    int y = ymin;
    int width = xmax*2;

    glBegin(GL_LINES);
        for( int i=0; i<width/2; i+=50)
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
}
