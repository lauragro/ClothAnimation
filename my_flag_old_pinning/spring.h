#ifndef SPRING_H
#define SPRING_H

#include "foundation.h"
#include "openglwidget.h"
#include "vector3d.h"
#include "particle.h"

class Spring
{
    public:
        // constructor/destructor
        Spring(Particle *particle1, Particle *particle2, int springType);
        Spring(Particle *particle1, int springType);
        ~Spring();

        // spring details
        Particle *particle1;
        Particle *particle2;
        double springConstant;
        double dampingConstant;
        double restLength;
        int springType;

        // draw function
        void draw();

        // force function
        Vector3D* force();
        Vector3D* forcePinned1();
        Vector3D* forcePinned2();

};

#endif // SPRING_H
