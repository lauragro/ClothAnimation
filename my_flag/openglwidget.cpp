#include <QtOpenGL>
#include "openglwidget.h"
#include "sim.h"
#include "window.h"


// simulation timer interval (millisec)
static int timer_interval = 10;

// Constructor
OpenGLWidget::OpenGLWidget(QWidget *parent) : QGLWidget(parent)
{
    mySim = new Sim();
    myCamera = new Camera();
    startup();
}

// Destructor
OpenGLWidget::~OpenGLWidget()
{
    cout << "widget deconstruction" << endl;
    delete mySim;
    delete myCamera;
}

// Connect to signals
void OpenGLWidget::startup()
{
    timer = new QTimer( this );
    frameTimer = new QTimer( this);
    connect( timer, SIGNAL(timeout()), this, SLOT(advanceTime( )) );
    connect( frameTimer, SIGNAL(timeout()), this, SLOT(advanceFrame()) );

    // initialize camera settings
    myCamera->startup();

    // TESTING
    /*simMode = true;
    timer->start( timer_interval );
    frameTimer->start( timer_interval );*/
}


// Initialize all graphics
void OpenGLWidget::initializeGL()
{
    // avoid the squashed look
    glViewport(0, 0, this->width(), this->height());

    // white background
    glClearColor(1, 1, 1, 1);

    // setup viewing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, this->width(), this->height(), 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

}

// Painting things
void OpenGLWidget::paintGL()
{
    // avoid the squashed look
    glViewport(0, 0, this->width(), this->height());

    // white background
    glClearColor(1, 1, 1, 1);

    // setup viewing ***************************/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, this->width(), this->height(), 0, -1, 1);

    // point the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /*gluLookAt(myCamera->CameraPos.x,    // eye x
       myCamera->CameraPos.y,           // eye y
       myCamera->CameraPos.z,           // eye z
              mySim->myBall->origin.x,        // centre x
              mySim->myBall->origin.y,       // centre y
              mySim->myBall->origin.z,        // centre z
              0.0, 1.0, 0.0);           // up xyz

    // rotate the camera
    /*glRotatef( myCamera->xangle, 1.0, 0.0, 0.0 );
    glRotatef( myCamera->yangle, 0.0, 1.0, 0.0 );
    glRotatef( myCamera->zangle, 0.0, 0.0, 1.0 );

    // zoom the camera
    glScalef( myCamera->scale, myCamera->scale, myCamera->scale );*/

    // testing
    /*glTranslatef(myCamera->CameraPos.x,    // eye x
                 myCamera->CameraPos.y,           // eye y
                 myCamera->CameraPos.z  );*/

    glMatrixMode(GL_MODELVIEW);
    /**********************************************/


    // Draw the scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // if a simulation is present, draw it
    if (mySim != NULL) mySim->draw();

}


/* Slots */

// Advance frame logic
void OpenGLWidget::advanceFrame()
{
    updateGL();

}

// Advance time logic
void OpenGLWidget::advanceTime()
{
    // if a simulation is present, advance it
    if (mySim != NULL) {
        mySim->simStep();
    }

    // if the sim should be stopped, stop it
    if (simMode == false) {
        timer->stop();
        cerr << "Simulation stopped \n";
    }

}

// Go button Logic
void OpenGLWidget::button_go()
{
    simMode = true;
    timer->start( timer_interval );
    frameTimer->start( timer_interval );

    cerr << "Button GO" << endl;
}

// Stop button logic
void OpenGLWidget::button_stop()
{
    simMode = false;
    timer->stop();
    frameTimer->stop();

    cerr << "Button STOP" << endl;

}

// Reset button logic
void OpenGLWidget::button_reset()
{
    button_stop();      // end current simulation
    mySim = new Sim();  // create new simulation
    startup();          // start timers
    advanceFrame();     // draw starting position

    //wait for button_go
}


/* 2D */
void OpenGLWidget::resizeGL( int winw, int winh )
{
    cerr << "resizing\n";
    glViewport( 0, 0, winw, winh );
    cerr << "width = " << winw << endl;
    cerr << "height = " << winh << endl;

    /*glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);*/

   // if (mySim != NULL) mySim->setSize(winw, winh );
}

void OpenGLWidget::mousePressEvent(QMouseEvent *e)
{
    myCamera->mousePressEvent(e);
    updateGL();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    myCamera->mouseReleaseEvent(e);
    updateGL();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    myCamera->mouseMoveEvent(e);
    updateGL();
}
