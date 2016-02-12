#include "sim.h"

// Constructor
Sim::Sim()
{
    cout << "Simulator Initialization\n";

    myFlag = new Flag();
    for(int i=0; i<myFlag->springsHigh; i++)
    {
        for(int j=0; j<myFlag->springsWide; j++)
        {
            myFlag->springs[i][j]->xCoord = (j+1)*50;
            myFlag->springs[i][j]->yCoord = (i+1)*50;

            // initialize wall coord to be coord of neighboring spring
            if(j>0)
            {
                myFlag->springs[i][j]->xCoordWall = myFlag->springs[i][j-1]->xCoord;
                myFlag->springs[i][j]->yCoordWall = myFlag->springs[i][j-i]->yCoord;
            }
        }
    }

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
    double radius = 10.0;

    // Draw blue circles
    for( int i=0; i<myFlag->springsHigh; i++ )
    {
        for(int j=0; j<myFlag->springsWide; j++)
        {
            drawCircle(myFlag->springs[i][j]->xCoord, myFlag->springs[i][j]->yCoord, radius, 20);
        }
    }

    // Draw connecting lines
    glPointSize(5.0);
    glLineWidth(2.0);
    for( int i=0; i<myFlag->springsHigh; i++ )
    {
        for( int j=1; j<myFlag->springsWide; j++ )
        {
            glBegin(GL_LINE_STRIP);
                //glVertex2f(myFlag->springs[i][j]->xCoordWall, myFlag->springs[i][j]->yCoordWall);

                glVertex2f(myFlag->springs[i][j-1]->xCoord, myFlag->springs[i][j-1]->yCoord);

                glVertex2f(myFlag->springs[i][j]->xCoord, myFlag->springs[i][j]->yCoord);
            glEnd();
        }
    }

    //cout << "x coord = " << myFlag->springs[0]->xCoord << endl;
    //cout << "y coord = " << myFlag->springs[0]->yCoord << endl;

}

// Simulation step using interpolation
void Sim::simStep()
{
    int type = 1;
    double dt = 0.1;

    switch (type)
    {
        case 0:
            rightStep(dt);
            break;
        case 1:
            eulerStep(dt);
            break;
        case 2:
            rungeKuttaStep(dt);
        default:
            break;
    }

}

// Move right simulation step
void Sim::rightStep(double dt)
{
    for(int i=0; i<myFlag->springsHigh; i++)
    {
        for(int j=0; j<myFlag->springsWide; j++)
        {
            myFlag->springs[i][j]->xCoord += 10;
        }
    }
}

// Euler simulation step
void Sim::eulerStep(double dt)
{
    int i,j;
    double v, a;
    for( i=0; i<myFlag->springsHigh; i++ )
    {
        for( j=0; j<myFlag->springsWide; j++ )
        {
            // update wall coord to be that of neighboring spring
            if(j>0)
            {
                myFlag->springs[i][j]->xCoordWall = myFlag->springs[i][j-1]->xCoord;
                myFlag->springs[i][j]->yCoordWall = myFlag->springs[i][j-i]->yCoord;
            }

            // set acceleration of spring
            a = acceleration(myFlag->springs[i][j]);

            // set velocity of spring
            v = myFlag->springs[i][j]->xVelocity;
            v = v + a*dt;
            myFlag->springs[i][j]->xVelocity = v;

            // set position of spring
            myFlag->springs[i][j]->xCoord += v * dt + a * dt * dt * 0.5;
        }

    }

}

// Runge Kutta simulation step
void Sim::rungeKuttaStep(double dt)
{
    int i,j;
    double h,x,v,a,k1,k2,k3,k4;
    h = dt;

    for(i=0; i<myFlag->springsHigh; i++)
    {
        for(j=0; j<myFlag->springsWide; j++)
        {
            // K1
            a = acceleration(myFlag->springs[i][j]);
            v = myFlag->springs[i][j]->xVelocity;
            v += a*dt;
            k1 = h * v;

            // K2
            a = acceleration(myFlag->springs[i][j]);
            // ...etc

        }
    }
}

// set acceleration of thisSpring
double Sim::acceleration(Spring *thisSpring)
{
    // get length of spring
    double length =  thisSpring->xCoord - thisSpring->xCoordWall;

    // limit stretch of spring
    if( length > 2.0*thisSpring->restLength )
    {
        length = 2.0* thisSpring->restLength;
    } else if( length < -2.0*thisSpring->restLength )
    {
        length = -2.0 * thisSpring->restLength;
    }

    // calculate acceleration
    double x = length - thisSpring->restLength;
    double v = thisSpring->xVelocity;
    double k = thisSpring->springConstant;
    double c = thisSpring->dampingConstant;
    double m = thisSpring->mass;
    double a = -1.0*(k*x + c*v)/m;

    // return acceleration
    return a;

}
