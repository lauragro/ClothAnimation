#include <QtOpenGL>
#include "openglwidget.h"
#include "sim.h"
#include "window.h"


// simulation timer interval (millisec)
static int timer_interval = 10;

// Constructor
OpenGLWidget::OpenGLWidget(QWidget *parent) : QGLWidget(parent)
{
    // test
    setFormat(QGLFormat(QGL::Rgba | QGL::DoubleBuffer | QGL::DepthBuffer));

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
    connect( timer, SIGNAL(timeout()), this, SLOT(advanceTime()) );
    connect( frameTimer, SIGNAL(timeout()), this, SLOT(advanceFrame()) );



    // initialize camera settings
    myCamera->startup(this->width(), this->height());

    /* Testing */
    cout << "widget thinks width is " << this->width() << endl;
    cout << "widget thinks height is " << this->height() << endl;

    // TESTING
    /*simMode = true;
    timer->start( timer_interval );
    frameTimer->start( timer_interval );*/

    // camera stuff
    // Initialize the camera and objects. This serves
        // as our constructor for the class.
        /*m_Camera = new Camera((float)this->width(), (float)this->height());

        // Display the grid by default.
        m_DrawGrid = GL_TRUE;

        // Allow objects to update by default.
        m_Play = GL_TRUE;*/
}


// Initialize all graphics
void OpenGLWidget::initializeGL()
{
    // avoid the squashed look
    glViewport(0, 0, this->width(), this->height());

    // white background
    glClearColor(1, 1, 1, 1);

    /* setup viewing *******************************/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // make centre of screen (0,0,0)
    glOrtho(-this->width(), this->width(),   // min/max x
            this->height(), -this->height(),  // min/max y
            -this->width(), this->width());  // min/max depth

    glMatrixMode(GL_MODELVIEW);

    /* Setup lighting ******************************/
    GLfloat light0_pos[] = {1.0,2.0,3.0,1.0};
    GLfloat light0_dir[] = {1.0,2.0,3.0,0.0};
    GLfloat diffuse0[] = {1.0,0.0,0.0,1.0};
    GLfloat ambient0[] = {1.0,0.0,0.0,1.0};
    GLfloat specular0[] = {1.0,1.0,1.0,1.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

    // add a small amount of white light everywhere
    GLfloat global_ambient[] = {0.1,0.1,0.1,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    timer->start(); // timer should run always, not tied to animation
    // frame timer is controlled by go and stop buttons

}

// Painting things
void OpenGLWidget::paintGL()
{
    //====Camera stuff from Lucky and 305 assignemnt===============
    myCamera->updatePos();
    //=============================================================

    //==================Camera operations===========================
    // Set the modelview matrix.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(myCamera->CameraPos.x, myCamera->CameraPos.y, myCamera->CameraPos.z,  // camera xyz
              0, 0, 0,       // target xyz
              0, 1, 0);      // up xyz
    //=============================================================

    // Draw the scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // if a simulation is present, draw it
    if (mySim != NULL) mySim->draw();

    /* Add lighting */    // DOESN'T WORK YET
    vec4 fColor = vec4(0.2, 0.2, 1, 1);
    //vec3 fpoint = (vec3)fColor;   // eye position
    vec3 fpoint = vec3(this->width()/2, this->height()/2, 0);
    //lighting
    vec3 L = vec3(100,100,1); //lightsource
    float intensity = 1.0;

    float light = intensity*glm::max(0.0f, dot(normalize(fpoint), normalize(L)));
    fColor += light;

}


/* Slots */

// Advance frame logic (animation stuff)
void OpenGLWidget::advanceFrame()
{
    // if a simulation is present, advance it
    if (mySim != NULL) {
        mySim->simStep();
    }

    // if the sim should be stopped, stop it
    if (simMode == false) {
        //timer->stop();// timer should run always, not tied to animation
        frameTimer->stop();
        cerr << "Simulation stopped \n";
    }

    updateGL();

}

// Advance time logic (camera stuff)
void OpenGLWidget::advanceTime()
{
    // if a simulation is present, advance it
    /*if (mySim != NULL) {
        mySim->simStep();
    }

    // if the sim should be stopped, stop it
    if (simMode == false) {
        //timer->stop();// timer should run always, not tied to animation
        frameTimer->stop();
        cerr << "Simulation stopped \n";
    }*/

    //====Camera stuff from Lucky and 305 assignment====
    myCamera->camera_phi += myCamera->camera_phi_speed;
    myCamera->camera_phi_speed *= 0.8;

    if (abs(myCamera->camera_phi_speed) < 1e-3)
    {
        myCamera->camera_phi_speed = 0;
    }

    myCamera->camera_theta += myCamera->camera_theta_speed;
    myCamera->camera_theta_speed *= 0.8;

    if (abs(myCamera->camera_theta_speed) < 1e-3)
    {
        myCamera->camera_theta_speed = 0;
    }
    //==================================================

    updateGL();

}

// Go button Logic
void OpenGLWidget::button_go()
{
    simMode = true;
    //timer->start( timer_interval ); // timer should run always, not tied to animation
    frameTimer->start( timer_interval );

    cerr << "Button GO" << endl;
}

// Stop button logic
void OpenGLWidget::button_stop()
{
    simMode = false;
    //timer->stop();    // timer should run always, not tied to animation
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

    // Defines the position of the camera and the target
     //glLoadIdentity();
     //gluLookAt(0, 80, 200, 0, 0, 0, 0, 1, 0);

    /*glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);*/

   // if (mySim != NULL) mySim->setSize(winw, winh );
}

void OpenGLWidget::mousePressEvent(QMouseEvent *e)
{
    //myCamera->mousePressEvent(e);

    myCamera->MouseButton(e, true); // Lucky's way
    updateGL();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    //myCamera->mouseReleaseEvent(e);   // no implementation yet?
    updateGL();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    //myCamera->mouseMoveEvent(e);

    myCamera->MouseMove(e->x(), e->y());    // Lucky's way
    updateGL();
}
