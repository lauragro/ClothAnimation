#include "spring.h"
#include "foundation.h"

// Constructors/destructor
Spring::Spring(Particle *particle1, Particle *particle2, int springType)
{
    glm::vec3 x,lengthVector;

    cout << "Spring Initialization\n";

    // Initialize spring details
    this->particle1 = particle1;
    this->particle2 = particle2;

    // Set spring type
    this->springType = springType;

    // rest length distance between 2 particles
    /*lengthVector = x->subtract(particle2->position, particle1->position);
    this->restLength = x->magnitude(lengthVector);*/
    lengthVector = particle2->position - particle1->position;
    this->restLength = (float)length(lengthVector);
    this->springLength = (float)length(lengthVector);  // initialize length to rest length

    // set spring constants struct > shear,bend
    switch(springType){
        case 0:
            this->springConstant = 10.0f;
            break;
        case 1:
            this->springConstant = 8.0f;
            break;
        default:
            this->springConstant = 8.0f;
    }

}

Spring::~Spring()
{
    cout << "Spring Destruction\n";
}

// draw the spring
void Spring::draw()
{
    glPointSize(5.0);
    glLineWidth(2.0);

    // different colours for different spring types
    switch(springType)
    {
        case 0:
            // blue structure springs
            glColor3f(0,0,1);
            //return; // for testing bend springs
            break;
        case 1:
            // green shear springs
            glColor3f(0,1,0);
            //return; // for testing bend springs
            break;
        case 2:
            // red bend springs
            glColor3f(1,0,0);
    }

    glBegin(GL_LINE_STRIP);
        glVertex2f(particle1->position.x, particle1->position.y);
        glVertex2f(particle2->position.x, particle2->position.y);
    glEnd();
}

// get spring force
glm::vec3 Spring::force()
{
    glm::vec3 force,lengthVector,v,x;

    // length = x2 - x1
    /*lengthVector = x->subtract(particle2->position, particle1->position);
    length = x->magnitude(lengthVector);*/
    lengthVector = particle1->position - particle2->position;
    springLength = (float)length(lengthVector);

    // calculate force if length does not equal rest length
    if( (springLength - restLength) >= EPSILON  )//&& springLength <= 1.5f*restLength)
    {

        /* Remove the stretch limitations - replace with stronger spring constants
        // limit stretch
        /*length = x->magnitude(lengthVector);
        if( length < restLength * 0.5 )
        {
            length = restLength * 0.5;
            lengthVector = x->scaleUp(x->normalize(lengthVector), length);
            if( particle2->pinned )
            {
                particle1->position = x->subtract(particle2->position, lengthVector);
            }
            else
            {
                particle2->position = x->add(particle1->position, lengthVector);
            }
        }
        else if( length > restLength * 1.5 )
        {
            length = restLength * 1.5;
            lengthVector = x->scaleUp(x->normalize(lengthVector), length);
            if( particle2->pinned )
            {
                particle1->position = x->subtract(particle2->position, lengthVector);
            }
            else
            {
                particle2->position = x->add(particle1->position, lengthVector);
            }
        }*/

        // x = (|L| - L0)(L/|L|)
        //x = x->scaleUp(x->normalize(lengthVector), length-restLength);
        x = normalize(lengthVector) * (springLength-restLength);


        // v = v2 - v1
        //v = x->subtract(particle2->velocity, particle1->velocity);
        v = particle1->velocity - particle2->velocity;

        // F = -kx, damping added later as +cv
        //force = x->scaleUp(x, -1.0*springConstant);
        force = -1.0f * springConstant * x;
        // F = -kx + cv
        //force = x->add(x->scaleUp(x, -1.0*springConstant), x->scaleUp(v, dampingConstant));

        return force;
    }
}

