#ifndef SPRING_H
#define SPRING_H

#include "foundation.h"
#include "openglwidget.h"

class Spring
{
    public:
        // spring details
        double dampingConstant;
        double mass;
        double restLength;
        double springConstant;

        double xCoord;
        double yCoord;

        // Coordinates of side of spring without mass
        double xCoordWall;
        double yCoordWall;

        // derivatives
        double xVelocity;
        double yVelocity;

        double xAcceleration;
        double yAcceleration;

        // constructor/destructor
        Spring();
        ~Spring();

};

#endif // SPRING_H
