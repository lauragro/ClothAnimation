#ifndef PARTICLE_H
#define PARTICLE_H

#include "foundation.h"
#include "vector3d.h"

class Particle
{
public:
    // constructors/destructor
    Particle();
    Particle(double x, double y, double z);
    Particle(Vector3D *position, Vector3D *velocity, Vector3D *acceleration);
    ~Particle();

    // attributes
    double mass;
    Vector3D *position;
    Vector3D *velocity;
    Vector3D *acceleration;
    Vector3D *force;
    Vector3D *externalForce;
    Vector3D *springForce;

    // draw function
    void draw();

};

#endif // PARTICLE_H
