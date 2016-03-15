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
    glMatrixMode(GL_MODELVIEW);

    glPointSize(5.0);
    glLineWidth(2.0);

    // different colours for different spring types
    switch(springType)
    {
        case 0:
            // blue structure springs
            glColor3f(0,0,1);
            break;
        case 1:
            // green shear springs
            glColor3f(0,1,0);
            break;
        case 2:
            // red bend springs
            glColor3f(1,0,0);
    }

    glBegin(GL_LINE_STRIP);
        glVertex3f(particle1->position.x, particle1->position.y, particle1->position.z);
        glVertex3f(particle2->position.x, particle2->position.y, particle2->position.z);
    glEnd();
}

// get spring force
glm::vec3 Spring::force()
{
    glm::vec3 force,lengthVector,v,x;

    // length = x2 - x1
    lengthVector = particle1->position - particle2->position;
    springLength = (float)length(lengthVector);

    // calculate force if length does not equal rest length
    if( (springLength - restLength) >= EPSILON  )//&& springLength <= 1.5f*restLength)
    {
        // x = (|L| - L0)(L/|L|)
        x = normalize(lengthVector) * (springLength-restLength);

        // v = v2 - v1
        v = particle1->velocity - particle2->velocity;

        // F = -kx, damping added later as +cv
        force = -1.0f * springConstant * x;

        return force;
    }
}

