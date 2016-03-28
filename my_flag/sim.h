// Interface for simulation class

#ifndef SIM_H
#define SIM_H

#include "foundation.h"
#include "spring.h"
#include "particle.h"
#include "flag.h"
#include "ball.h"
#include "ground.h"

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
        void draw(GLuint * textures);

        // Progesses the simulation forward
        void simStep();
        void rightStep(float dt);
        void eulerStep(float dt);
        void rungeKuttaStep(float dt);
        float acceleration(Particle *thisParticle);
        void updateForces(int number);

        // Check for collisions of one particle
        bool collidesWithBall(Particle * thisParticle, int number);
        bool collidesWithGround(Particle * thisParticle, int number);

        // The components belonging to this simulation
        Flag * myFlag;
        Ball * myBall;
        Ground * myGround;

        // Time of sim
        float t;
};

#endif // SIM_H
