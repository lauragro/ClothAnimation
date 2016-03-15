#include "ground.h"

// Constructor
Ground::Ground(int width)
{
    y = 100.0;
}

// Destructor
Ground::~Ground()
{

}

// Draw function
Ground::draw()
{
    // uncomment below to draw ground with lines instead of texture mapping

    /*
    // avoid attaching ground to ball
    glPushMatrix();

    glColor3f(0.5,0.5,0.5);

    /*glBegin(GL_LINES);
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
    glEnd();*/
    //glPopMatrix();

    /* Make the grass */
    testTextures();

}

//========TEXTURES================================================
void Ground::LoadGLTextures( const char * name )
{
    QImage img;

    if(!img.load(name)){
        std::cerr << "ERROR in loading image" << std::endl;
    }

    QImage t = QGLWidget::convertToGLFormat(img);

    glGenTextures(1, &texBufferID);
    glBindTexture(GL_TEXTURE_2D, texBufferID);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits());

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glBindTexture( GL_TEXTURE_2D, 0 );
}



void Ground::initializeShader()
{
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_TEXTURE_2D);
    LoadGLTextures("../grass.bmp");

}

// testing, this should probably go in paintGL
void Ground::testTextures()
{
    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //float y = 100.0;

    glShadeModel( GL_SMOOTH );
        glEnable(GL_TEXTURE_2D);
        glColor3f(0.5, 0.5, 0);
        glBindTexture(GL_TEXTURE_2D, texBufferID);

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-256.0f, y, 256.0f);  // vertex 1
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-256.0f, y, -256.0f); // vertex 2
            glTexCoord2f(1.0f, 0.0f); glVertex3f(256.0f, y, -256.0f);  // vertex 3
            glTexCoord2f(1.0f, 1.0f); glVertex3f(256.0f, y, 256.0f);   // vertex 4
        glEnd();
        glDisable(GL_TEXTURE_2D);

        // testing now - will use above later
        xmin = -256.0f;
        zmin = xmin;
        xmax = 256.0f;
        zmax = xmax;
}
