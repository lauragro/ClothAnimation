#ifndef LIMB_H
#define LIMB_H

#include "particle.h"

class Limb
{
public:
    Limb(vec3 start, vec3 end);
    ~Limb();

    vec3 start, end;

    void draw();
    bool collidesWith(Particle *p, int number);
};

#endif // LIMB_H
