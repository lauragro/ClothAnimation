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
    startup();
}

// Destructor
OpenGLWidget::~OpenGLWidget()
{

}

// Connect to signals
void OpenGLWidget::startup()
{
    timer = new QTimer( this );
    frameTimer = new QTimer( this);
    connect( timer, SIGNAL(timeout()), this, SLOT(advanceTime( )) );
    connect( frameTimer, SIGNAL(timeout()), this, SLOT(advanceFrame()) );

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

    // setup viewing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, this->width(), this->height(), 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

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
