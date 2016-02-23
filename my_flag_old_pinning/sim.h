// Interface for simulation class

#ifndef SIM_H
#define SIM_H

#include "foundation.h"
#include "spring.h"
#include "particle.h"
#include "flag.h"

class Flag;
class Spring;
class Vector3D;

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
        void rightStep(double dt);
        void eulerStep(double dt);
        void rungeKuttaStep(double dt);
        double acceleration(Particle *thisParticle);
        void updateForces();

        // The spring objects belonging to this simulation
        Flag * myFlag;
};

#endif // SIM_H
