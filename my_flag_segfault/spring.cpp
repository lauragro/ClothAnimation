#include "spring.h"
#include "foundation.h"

// Constructors/destructor
Spring::Spring(Particle *particle1, Particle *particle2, int springType)
{
    cout << "Spring Initialization\n";

    // Initialize spring details
    this->particle1 = particle1;
    this->particle2 = particle2;

    this->restLength = 20;
    this->springConstant = 1.0;
    this->dampingConstant = 0.8;
    this->springType = springType;
}

Spring::Spring(Particle *particle1, int springType)
{
    cout << "Spring Initialization\n";

    // Initialize spring details
    this->particle1 = particle1;

    this->restLength = 20;
    this->springConstant = 1.0;
    this->dampingConstant = 0.8;
    this->springType = springType;
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
        glVertex2f(particle1->position->x, particle1->position->y);
        glVertex2f(particle2->position->x, particle2->position->y);
    glEnd();
}

// get spring force
Vector3D* Spring::force()
{
    Vector3D *force;
    Vector3D *lengthVector;
    Vector3D *v;
    Vector3D *x;

    // length = x2 - x1
    lengthVector = x->subtract(particle2->position, particle1->position);

    // limit stretch
    length = x->magnitude(lengthVector);
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
    }

    // x = (|L| - L0)(L/|L|)
    x = x->scaleUp(x->normalize(lengthVector), length-restLength);

    // v = v2 - v1
    v = x->subtract(particle2->velocity, particle1->velocity);

    // F = -kx + cv
    force = x->add(x->scaleUp(x, -1.0*springConstant), x->scaleUp(v, dampingConstant));

    return force;
}

