#include "spring.h"
#include "foundation.h"

// Constructors/destructor
Spring::Spring(Particle *particle1, Particle *particle2, int springType)
{
    Vector3D *x = new Vector3D;
    Vector3D *lengthVector;

    cout << "Spring Initialization\n";

    // Initialize spring details
    this->particle1 = particle1;
    this->particle2 = particle2;

    // Set spring type
    this->springType = springType;

    // rest length distance between 2 particles
    lengthVector = x->subtract(particle2->position, particle1->position);
    this->restLength = x->magnitude(lengthVector);


    // set spring constants struct > shear,bend
    switch(springType){
        case 0:
            this->springConstant = .5;
            break;
        case 1:
            this->springConstant = .4;
            break;
        default:
            this->springConstant = .4;
    }

    // set damping constants
    this->dampingConstant = 0.5;



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
    Vector3D *force = new Vector3D();
    Vector3D *lengthVector;
    Vector3D *v;
    Vector3D *x;

    // length = x2 - x1
    lengthVector = x->subtract(particle2->position, particle1->position);
    length = x->magnitude(lengthVector);

    // calculate force if length does not equal rest length
    if( (length - restLength) > EPSILON )// && (length - restLength) < 0.5*restLength)
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
        x = x->scaleUp(x->normalize(lengthVector), length-restLength);

        // v = v2 - v1
        v = x->subtract(particle2->velocity, particle1->velocity);

        // F = -kx, damping added later as +cv
        force = x->scaleUp(x, -1.0*springConstant);

        // F = -kx + cv
        //force = x->add(x->scaleUp(x, -1.0*springConstant), x->scaleUp(v, dampingConstant));

        return force;
    }
}

