#include "sim.h"

// Constructor
Sim::Sim()
{
    cout << "Simulator Initialization\n";
    mySpring = new Spring();
}

// Destructor
Sim::~Sim()
{
    cout << "Simulator Destruction\n";
    delete this;
}

// Draw circle using triangle fan
void Sim::drawCircle(double x, double y, double radius, double resolution)
{
    cout << "circ x draw = " << x << endl;
    cout << "circ y draw = " << y << endl;

    // Compute angle of each triangle in fan
    double theta = 2.0 * PI / resolution;

    glColor3f(0,0.4,0.6);
    glBegin(GL_TRIANGLE_FAN);

        glVertex2f(x,y);  // centre point
        for( int i=0; i<=resolution; i++ )
        {
            // Apply the Pythagorean Theorem to get next point
            glVertex2f(
                x + radius * sin( i * theta ),
                y + radius * cos( i * theta )
            );
        }
    glEnd();

}

// Draw everything on screen
void Sim::draw()
{
    double radius = 25.0;

    // Draw square
    glBegin(GL_QUADS);
        glVertex2f(0, mySpring->yCoordWall + radius);
        glVertex2f(0, mySpring->yCoordWall - radius);
        glVertex2f(50, mySpring->yCoordWall - radius);
        glVertex2f(50, mySpring->yCoordWall + radius);
    glEnd();

    // Draw blue circle
    drawCircle(mySpring->xCoord, mySpring->yCoord, radius, 20);

    // Draw connecting line
    glPointSize(5.0);
        glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
        glVertex2f(mySpring->xCoordWall, mySpring->yCoordWall);
        glVertex2f(mySpring->xCoord, mySpring->yCoord);
    glEnd();

    cout << "x coord = " << mySpring->xCoord << endl;
    cout << "y coord = " << mySpring->yCoord << endl;

}

// Simulation step using interpolation
void Sim::simStep()
{
    double dt = 0.1;

    // Move mass right
    //mySpring->xCoord += 10;

    // Euler step
    double length =  mySpring->xCoord - mySpring->xCoordWall;
    if( length > 2.0*mySpring->restLength )
    {
        length = mySpring->restLength;
    } else if( length < -2.0*mySpring->restLength )
    {
        length = -1.0 * mySpring->restLength;
    }

    double x = mySpring->xCoord - mySpring->restLength; // because stationary block is at (x=0)
    double v = mySpring->xVelocity;
    double k = mySpring->springConstant;
    double c = mySpring->dampingConstant;
    double m = mySpring->mass;
    double a = -1.0*(k*x + c*v)/m;
    mySpring->xAcceleration = a;

    v = v + a*dt;
    mySpring->xVelocity = v;

    mySpring->xCoord += v * dt + a * dt * dt * 0.5;

    // RK4 step
    /*double k1, k2, k3, k4, a1, a2, a3, a4, h;
    double length = abs(mySpring->xCoordWall - mySpring->xCoord);

    // position step
    h = mySpring->xVelocity * dt + 0.5 * mySpring->xAcceleration * dt * dt;
    // acceleration
    a1 = mySpring->springConstant * (length - mySpring->restLength)
                /mySpring->mass - mySpring->dampingConstant * mySpring->xVelocity;
    a2 = mySpring->springConstant * (length + 0.5*mySpring->xVelocity - )

    // velocity
    k1 = dt * mySpring->xAcceleration;
    k2 =*/

}
