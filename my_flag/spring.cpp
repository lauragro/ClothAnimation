#include "spring.h"

// Constructor/destructor
Spring::Spring()
{
    cout << "Spring Initialization\n";

    // Initialize spring details

    dampingConstant = 0.0;
    mass = 1.0;
    restLength = 100;
    springConstant = 1.0;

    /*xCoord = 150.0;
    yCoord = 300.0;

    // Coordinates of side of spring without mass
    xCoordWall = 0.0;
    yCoordWall = 300.0;*/

    // Derivatives
    xVelocity = 0.0;
    yVelocity = 0.0;

    xAcceleration = 0.0;
    yAcceleration = 0.0;
}

Spring::~Spring()
{
    cout << "Spring Destruction\n";
}


