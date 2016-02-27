// Interface for simulation class

#ifndef SIM_H
#define SIM_H

#include "foundation.h"
#include "spring.h"
#include "particle.h"
#include "flag.h"

class Flag;
class Spring;
class vec3;

class Sim
{
    public:
        // Constructor/destructor
        Sim();
        ~Sim();

        // Draws all graphics
        void draw();

        // Progesses the simulation forward
        void simStep();
        void rightStep(float dt);
        void eulerStep(float dt);
        void rungeKuttaStep(float dt);
        float acceleration(Particle *thisParticle);
        void updateForces();

        // The spring objects belonging to this simulation
        Flag * myFlag;
};

#endif // SIM_H
