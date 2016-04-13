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
            this->springConstant = 18.0f;//28.0f;//14.0f;
            break;
        case 1:
            this->springConstant = 16.0f;//24.0f;//12.0f;
            break;
        default:
            this->springConstant = 16.0f;//24.0f;//12.0f;
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
        default://case 2:
            // red bend springs
            glColor3f(1,0,0);
    }

    glBegin(GL_LINE_STRIP);
        glVertex3f(particle1->position.x, particle1->position.y, particle1->position.z);
        glVertex3f(particle2->position.x, particle2->position.y, particle2->position.z);
    glEnd();
}

// get spring force
glm::vec3 Spring::force(int number)
{
    glm::vec3 force,lengthVector,v,x;

    // length = x2 - x1
    switch(number){
    case 0:
        lengthVector = particle1->position - particle2->position;
        break;
    case 1:
        lengthVector = particle1->position1 - particle2->position1;
        break;
    case 2:
        lengthVector = particle1->position2 - particle2->position2;
        break;
    default://case 3:
        lengthVector = particle1->position3 - particle2->position3;

    }
    //lengthVector = particle1->position - particle2->position;
    springLength = (float)length(lengthVector);

    // calculate force if length does not equal rest length
    if( abs(springLength - restLength) >= EPSILON  )//&& springLength <= 1.5f*restLength)
    {
        // x = (|L| - L0)(L/|L|)
        x = normalize(lengthVector) * (springLength-restLength);

        // v = v2 - v1
        /*switch(number){   // don't need v here!
        case 0:
            v = particle1->velocity - particle2->velocity;
        case 1:
            v = particle1->velocity1 - particle2->velocity1;
        case 2:
            v = particle1->velocity2 - particle2->velocity2;
        case 3:
            v = particle1->velocity3 - particle2->velocity3;

        }*/

        // F = -kx, damping added later as +cv
        force = -1.0f * springConstant * x * 0.5f;

        return force;
    }
}

