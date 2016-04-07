#include <QtOpenGL>
#include "openglwidget.h"
#include "sim.h"
#include "window.h"
#include <QKeyEvent>
#include <QKeySequence>

// simulation timer interval (millisec)
static int timer_interval = 10;

// Constructor
OpenGLWidget::OpenGLWidget(QWidget *parent) : QGLWidget(parent)
{
    // test
    //setFormat(QGLFormat(QGL::Rgba | QGL::DoubleBuffer | QGL::DepthBuffer));

    mySim = new Sim();
    myCamera = new Camera();
    startup();

    // set focus policy for responding to keyboard events
    this->setFocusPolicy(Qt::StrongFocus);
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

}


// Initialize all graphics
void OpenGLWidget::initializeGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // white background
    //glClearColor(1, 1, 1, 1);

    /* setup viewing *******************************/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1,1,-0.75f,0.75f,1,5000);    // hard coding the view box ratio here!

    glMatrixMode(GL_MODELVIEW);

    // white background
    glClearColor(1, 1, 1, 1);

    /* setup shaders ********************************/
    initializeShader();

    /* Setup lighting ******************************/
    GLfloat light0_pos[] = {0.0,0.0,10.0,1.0};
    GLfloat light0_dir[] = {0.0,0.0,0.0,0.0};
    GLfloat diffuse0[] = {0.0,0.0,1.0,1.0};
    GLfloat ambient0[] = {0.5,0.5,0.5,1.0};
    GLfloat specular0[] = {1.0,1.0,1.0,1.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

    // add a small amount of white light everywhere
    GLfloat global_ambient[] = {0.5,0.5,0.5,1.0};
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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gluLookAt(myCamera->CameraPos.x, myCamera->CameraPos.y, myCamera->CameraPos.z,  // camera xyz
              0, 0, 0,       // target xyz
              0, -1, 0);      // up xyz*/
    //=============================================================


    // if a simulation is present, draw it
    if (mySim != NULL) mySim->draw(textures);

}


/* Slots */

// Advance frame logic (animation stuff)
void OpenGLWidget::advanceFrame()
{
    // if a simulation is present, advance it
    if (mySim != NULL)
    {
        mySim->simStep();
    }

    // if the sim should be stopped, stop it
    if (simMode == false)
    {
        //timer->stop();// timer should run always, not tied to animation
        frameTimer->stop();
        cerr << "Simulation stopped \n";
    }

    updateGL();

}

// Advance time logic (camera stuff)
void OpenGLWidget::advanceTime()
{


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
    frameTimer->start( timer_interval );

    cerr << "Button GO" << endl;
}

// Stop button logic
void OpenGLWidget::button_stop()
{
    simMode = false;
    frameTimer->stop();

    cerr << "Button STOP" << endl;

}

// Reset button logic
void OpenGLWidget::button_reset()
{
    button_stop();      // end current simulation
    mySim = new Sim();  // create new simulation
    initializeShader();    //reset grass etc.
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

/********** React to mouse buttons ***********/
void OpenGLWidget::mousePressEvent(QMouseEvent *e)
{
    myCamera->MouseButton(e, true);
    updateGL();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    myCamera->MouseButton(e, false);
    updateGL();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    myCamera->MouseMove(e->x(), e->y());
    updateGL();
}

/*********** React to keyboard buttons ********/
void OpenGLWidget::keyPressEvent(QKeyEvent *k)
{
    // Amount to move per step
    float stepSize = 10.0f;

    // Left arrow
    if(k->matches(QKeySequence::MoveToPreviousChar))
    //if(k->matches(QKeySequence(Qt::Key_A)))
    {
        vec3 p = vec3(mySim->myPerson->origin.x + stepSize,
                      mySim->myPerson->origin.y,
                      mySim->myPerson->origin.z);

        mySim->myPerson->setOrigin(p);

        cout << "LEFT ARROW" << endl;

        // assure the simulation step occurs
        advanceFrame();
    }
    // Right arrow
    else if(k->matches(QKeySequence::MoveToNextChar))
    {
        vec3 p = vec3(mySim->myPerson->origin.x - stepSize,
                      mySim->myPerson->origin.y,
                      mySim->myPerson->origin.z);

        mySim->myPerson->setOrigin(p);

        cout << "RIGHT ARROW" << endl;

        // assure the simulation step occurs
        advanceFrame();
    }
    // Up arrow
    else if(k->matches(QKeySequence::MoveToPreviousLine))
    {
        vec3 p = vec3(mySim->myPerson->origin.x,
                      mySim->myPerson->origin.y,
                      mySim->myPerson->origin.z - stepSize);

        mySim->myPerson->setOrigin(p);

        cout << "UP ARROW" << endl;

        // assure the simulation step occurs
        advanceFrame();
    }
    // Down arrow
    else if(k->matches(QKeySequence::MoveToNextLine))
    {
        vec3 p = vec3(mySim->myPerson->origin.x,
                      mySim->myPerson->origin.y,
                      mySim->myPerson->origin.z + stepSize);

        mySim->myPerson->setOrigin(p);

        cout << "DOWN ARROW" << endl;

        // assure the simulation step occurs
        advanceFrame();
    }

    //k = NULL;
    //updateGL();
}


//========TEXTURES================================================
void OpenGLWidget::Load2DGLTexture( const char * name, const int texID )
{
    QImage img;

    if(!img.load(name)){
        std::cerr << "ERROR in loading image" << std::endl;
    }

    QImage t = QGLWidget::convertToGLFormat(img);

    glGenTextures(1, &textures[texID]);
    glBindTexture(GL_TEXTURE_2D, textures[texID]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits());

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glDisable(GL_TEXTURE_2D);
}

void OpenGLWidget::LoadSphereGLTexture( const char * name, const int texID )
{
    QImage img;

    if(!img.load(name)){
        std::cerr << "ERROR in loading image" << std::endl;
    }

    QImage t = QGLWidget::convertToGLFormat(img);

    glGenTextures(1, &textures[texID]);
    glBindTexture(GL_TEXTURE_2D, textures[texID]);  // THIS TEXTURE APPEARS WHEN GL_TEXTURE_2D IS USED INSTEAD
        glTexImage2D(GL_TEXTURE_2D, 0, 3, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits());
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        /*GLfloat planes[] = {0.5, 0.0, 0.0, 0.5}; // s = x/2 + 1/2
        GLfloat planet[] = {0.0, 0.5, 0.0, 0.5}; // t = y/2 + 1/2
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGenfv(GL_S, GL_SPHERE_MAP, planes);
        glTexGenfv(GL_T, GL_SPHERE_MAP, planet);*/

    glDisable(GL_TEXTURE_2D);
}

void OpenGLWidget::initializeShader()
{
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_TEXTURE_2D);
    Load2DGLTexture("../grass.bmp",0);
    LoadSphereGLTexture("../volleyball.jpg",1);

}
