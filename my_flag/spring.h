#ifndef SPRING_H
#define SPRING_H

#include "foundation.h"
#include "openglwidget.h"
#include "particle.h"

class Spring
{
    public:
        // constructor/destructor
        Spring(Particle *particle1, Particle *particle2, int springType);
        ~Spring();

        // spring details
        Particle *particle1;
        Particle *particle2;
        float springConstant;
        float dampingConstant;
        float restLength;
        float springLength;
        int springType;

        // draw function
        void draw();

        // force function
        glm::vec3 force();

};

#endif // SPRING_H
