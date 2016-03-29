#include "person.h"

Person::Person()
{
    head = new Ball(0);
    body = new Ball(0);
    head->origin = body->origin - vec3(0.0f, 3.0f*body->radius, 0.0f);   // move head up
    body->radius = 2.0f * head->radius; // increase body size
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
void Person::draw(GLuint headTexture, GLuint bodyTexture)
{
    body->draw(bodyTexture);
    head->draw(headTexture);

}
