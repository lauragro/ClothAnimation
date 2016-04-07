#ifndef PARTICLE_H
#define PARTICLE_H

#include "foundation.h"

class Particle
{
public:
    // constructors/destructor
    Particle();
    Particle(float x, float y, float z);
    Particle(vec3 position, vec3 velocity, vec3 acceleration);
    ~Particle();

    // attributes
    float mass;
    vec3 position;
    vec3 velocity;
    vec3 acceleration;
    vec3 force;
    vec3 externalForce;
    vec3 springForce;
    vec3 gravityForce;
    bool pinned = false;
    vec3 normal;    // not of unit length as it is a
                    // sum of neighboring triangle normals at each step

    // attributes for RK4 integration
    vec3 position1;
    vec3 position2;
    vec3 position3;
    vec3 velocity1;
    vec3 velocity2;
    vec3 velocity3;

    // draw function
    void draw();

};

#endif // PARTICLE_H
