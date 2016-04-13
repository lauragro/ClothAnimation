#include "particle.h"

// default constructor
/*Particle::Particle()
{
    mass = 1.0f;
    gravityForce = vec3(0.0f,9.81f,0.0f);
}*/

// position constructor
Particle::Particle(float x, float y, float z)
{
    mass = 1.0f;
    position = position_old = vec3(x, y, z);
    position1 = vec3(x, y, z);
    position2 = vec3(x, y, z);
    position3 = vec3(x, y, z);
    velocity = velocity_old = vec3(0.0f,0.0f,0.0f);
    velocity1 = vec3(0.0f,0.0f,0.0f);
    velocity2 = vec3(0.0f,0.0f,0.0f);
    velocity3 = vec3(0.0f,0.0f,0.0f);
    gravityForce = vec3(0.0f,9.81f,0.0f);

    acceleration = acceleration_old = vec3(0.0f,0.0f,0.0f);

    pinned = false;
}

// total state constructor
/*Particle::Particle(vec3 position, vec3 velocity, vec3 acceleration)
{
    mass = 1.0f;
    this->position = position;
    this->velocity = velocity;
    this->acceleration = acceleration;
    gravityForce = vec3(0.0f,9.81f,0.0f);
}*/

// destructor
Particle::~Particle()
{
    cout << "Particle deconstruction" << endl;
}

// Draw function
void Particle::draw()
{
    glMatrixMode(GL_MODELVIEW);

    // get the coordinates and radius
    float x = position.x;
    float y = position.y;
    float z = position.z;
    float radius = 5.0f;
    float resolution = 20.0f;

    // Compute angle of each triangle in fan
    float theta = 2.0f * PI / resolution;

    glColor3f(0,0.4,0.6);
    glBegin(GL_TRIANGLE_FAN);

        glVertex3f(x, y, z);  // centre point
        for( int i=0; i<=resolution; i++ )
        {
            // Apply the Pythagorean Theorem to get next point
            glVertex3f(
                x + radius * sin( i * theta ),
                y + radius * cos( i * theta ),
                        z
            );
        }
    glEnd();
}
