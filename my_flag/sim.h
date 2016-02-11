// Interface for simulation class

#ifndef SIM_H
#define SIM_H

#include "foundation.h"
#include "spring.h"
#include "flag.h"

class Flag;
class Spring;

class Sim
{
    public:
        // Constructor/destructor
        Sim();
        ~Sim();

        // Draws all graphics
        void drawCircle(double x, double y, double radius, double resolution);
        void draw();

        // Progesses the simulation forward
        void simStep();

        // The spring objects belonging to this simulation
        Flag * myFlag;
};

#endif // SIM_H
