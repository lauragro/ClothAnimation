#include "person.h"

Person::Person()
{
    head = new Ball(0);
    body = new Ball(0);

    body->origin = origin;

    head->origin = body->origin - vec3(0.0f, 3.0f*body->radius, 0.0f);   // move head up
    body->radius = 2.0f * head->radius; // increase body size

    coefficientOfFriction = 10.0f;   // TODO: experiment to find a good one

    /*vec3 limbStart = body->origin - vec3(body->radius, 0.0f, 0.0f);   // add limbs if there's time :)
    vec3 limbEnd = limbStart - vec3(body->radius, 0.0f, 0.0f);
    leftArm = new Limb(limbStart, limbEnd);
    rightArm = new Limb(limbStart, limbEnd);
    leftLeg = new Limb(limbStart, limbEnd);
    rightLeg = new Limb(limbStart, limbEnd);*/
}
Person::~Person()
{

}
bool Person::collidesWith(Particle *p)
{
    // check head
    if(head->collidesWith(p,0))
    {
        // collision found
        return true;
    }

    // check body
    if(body->collidesWith(p,0))
    {
        // collision found
        return true;
    }

    // no collision
    return false;
}
void Person::setOrigin(vec3 p)
{
    origin = p;
    body->origin = p;
    head->origin = body->origin - vec3(0.0f, body->radius + head->radius, 0.0f);

}

void Person::draw(GLuint headTexture, GLuint bodyTexture)
{
    body->draw(bodyTexture);
    head->draw(headTexture);

}
