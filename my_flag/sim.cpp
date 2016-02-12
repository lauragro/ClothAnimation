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

    // Draw square
    /*glBegin(GL_QUADS);
        glVertex2f(0, mySprings[0]->yCoordWall + radius);
        glVertex2f(0, mySprings[0]->yCoordWall - radius);
        glVertex2f(50, mySprings[0]->yCoordWall - radius);
        glVertex2f(50, mySprings[0]->yCoordWall + radius);
    glEnd();*/

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
    double dt = 0.1;

    // Move mass right
    /*for(int i=0; i<myFlag->springsHigh; i++)
    {
        for(int j=0; j<myFlag->springsWide; j++)
        {
            myFlag->springs[i][j]->xCoord += 10;
        }
    }*/

    // Euler step
    for( int i=0; i<myFlag->springsHigh; i++ )
    {
        for( int j=0; j<myFlag->springsWide; j++ )
        {
            // update wall coord to be that of neighboring spring
            if(j>0)
            {
                myFlag->springs[i][j]->xCoordWall = myFlag->springs[i][j-1]->xCoord;
                myFlag->springs[i][j]->yCoordWall = myFlag->springs[i][j-i]->yCoord;
            }

            double length =  myFlag->springs[i][j]->xCoord - myFlag->springs[i][j]->xCoordWall;
            if( length > 2.0*myFlag->springs[i][j]->restLength )
            {
                length = 2.0* myFlag->springs[i][j]->restLength;
            } else if( length < -2.0*myFlag->springs[i][j]->restLength )
            {
                length = -2.0 * myFlag->springs[i][j]->restLength;
            }

            double x = length - myFlag->springs[i][j]->restLength;
            double v = myFlag->springs[i][j]->xVelocity;
            double k = myFlag->springs[i][j]->springConstant;
            double c = myFlag->springs[i][j]->dampingConstant;
            double m = myFlag->springs[i][j]->mass;
            double a = -1.0*(k*x + c*v)/m;
            myFlag->springs[i][j]->xAcceleration = a;

            v = v + a*dt;
            myFlag->springs[i][j]->xVelocity = v;

            myFlag->springs[i][j]->xCoord += v * dt + a * dt * dt * 0.5;
        }
    }

    // RK4 step
    /*double k1, k2, k3, k4, a1, a2, a3, a4, h;
    double length = abs(mySprings[0]->xCoordWall - mySprings[0]->xCoord);

    // position step
    h = mySprings[0]->xVelocity * dt + 0.5 * mySprings[0]->xAcceleration * dt * dt;
    // acceleration
    a1 = mySprings[0]->springConstant * (length - mySprings[0]->restLength)
                /mySprings[0]->mass - mySprings[0]->dampingConstant * mySprings[0]->xVelocity;
    a2 = mySprings[0]->springConstant * (length + 0.5*mySprings[0]->xVelocity - )

    // velocity
    k1 = dt * mySprings[0]->xAcceleration;
    k2 =*/

}
