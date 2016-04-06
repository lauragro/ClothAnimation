#ifndef PERSON_H
#define PERSON_H

#include "ball.h"
#include "ground.h"
#include "particle.h"
#include "limb.h"

class Person
{
public:
    Person();
    ~Person();

    vec3 origin;    // origin of body

    Ball * head;
    Ball * body;
    /*Limb * leftArm;   // add limbs if there's time :)
    Limb * rightArm;
    Limb * leftLeg;
    Limb * rightLeg;*/

    bool collidesWith(Particle *p);

    void draw(GLuint headTexture, GLuint bodyTexture);

    void setOrigin(vec3 p);

};

#endif // PERSON_H
