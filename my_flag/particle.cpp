#include "particle.h"

// default constructor
Particle::Particle()
{
    mass = 1.0;
    position = new Vector3D();
    velocity = new Vector3D();
    acceleration = new Vector3D();
    force = new Vector3D();
    externalForce = new Vector3D();
    springForce = new Vector3D();
}

// position constructor
Particle::Particle(double x, double y, double z)
{
    mass = 1.0;
    position = new Vector3D(x, y, z);
    velocity = new Vector3D();
    acceleration = new Vector3D();
    force = new Vector3D();
    externalForce = new Vector3D();
    springForce = new Vector3D();
}

// total state constructor
Particle::Particle(Vector3D *position, Vector3D *velocity, Vector3D *acceleration)
{
    mass = 1.0;
    this->position = position;
    this->velocity = velocity;
    this->acceleration = acceleration;
    force = new Vector3D();
    externalForce = new Vector3D();
    springForce = new Vector3D();
}

// destructor
Particle::~Particle()
{
    cout << "Particle deconstruction" << endl;
}

// Draw function
void Particle::draw()
{
    // get the coordinates and radius
    double x = position->x;
    double y = position->y;
    double radius = 5.0;
    double resolution = 20;

    // Compute angle of each triangle in fan
    double theta = 2.0 * PI / resolution;

    glColor3f(0,0.4,0.6);
    glBegin(GL_TRIANGLE_FAN);

        glVertex2f(x, y);  // centre point
        for( int i=0; i<=resolution; i++ )
        {
            // Apply the Pythagorean Theorem to get next point
            glVertex2f(
                x + radius * sin( i * theta ),
                y + radius * cos( i * theta )
            );
        }
    glEnd();
}
