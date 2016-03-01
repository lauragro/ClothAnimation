// Interface for simulation class

#ifndef SIM_H
#define SIM_H

#include "foundation.h"
#include "spring.h"
#include "particle.h"
#include "flag.h"
#include "ball.h"

class Flag;
class Spring;
//class vec3;

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

        // Check for collision of one particle with ball
        bool collidesWithBall(Particle * thisParticle);

        // The flag and ball belonging to this simulation
        Flag * myFlag;
        Ball * myBall;
};

#endif // SIM_H
