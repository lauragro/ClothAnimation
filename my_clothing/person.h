#ifndef PERSON_H
#define PERSON_H

#include "ball.h"
#include "ground.h"
#include "particle.h"

class Person
{
public:
    Person();
    ~Person();

    Ball * head;
    Ball * body;

    bool collidesWith(Particle *p);

    void draw(GLuint headTexture, GLuint bodyTexture);

};

#endif // PERSON_H
