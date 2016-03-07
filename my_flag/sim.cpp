#include "sim.h"
#include "foundation.h"

// Constructor
Sim::Sim()
{
    cout << "Simulator Initialization\n";

    myFlag = new Flag();

    myBall = new Ball();

    t = 0;

}

// Destructor
Sim::~Sim()
{
    cout << "Simulator Destruction\n";
    delete myFlag;
}

// Draw everything on screen
void Sim::draw()
{

    // Draw blue circles
    /*for( int i=0; i<myFlag->particlesHigh; i++ )
    {
        for(int j=0; j<myFlag->particlesWide; j++)
        {
            myFlag->particles[i][j]->draw();
        }
    }*/

    // Draw connecting lines
    for( int i=0; i<myFlag->implementedSprings; i++ )
    {
        myFlag->springs[i]->draw();
    }

    // Draw ball
    myBall->draw();

}

// Simulation step using interpolation
void Sim::simStep()
{
    int type = 1;
    float dt = 0.2f;
    t += dt;

    switch (type)
    {
        case 0:
            rightStep(dt);
            break;
        case 1:
            eulerStep(dt);
            break;
        case 2:
            rungeKuttaStep(dt);
        default:
            break;
    }

}

// Move right simulation step
void Sim::rightStep(float dt)
{
    for(int i=0; i<myFlag->particlesHigh; i++)
    {
        for(int j=0; j<myFlag->particlesWide; j++)
        {
            myFlag->particles[i][j]->position.x += 10;
        }
    }
}

// Euler simulation step
void Sim::eulerStep(float dt)
{
    int i,j;
    glm::vec3 x, v, a;

    // move the ball a bit
    myBall->origin += vec3(10*sin(t/12), 0, 0);

    // update forces on particles
    updateForces();

    // update velocities and positions of particles
    for( i=0; i<myFlag->particlesHigh; i++ )
    {
        for( j=0; j<myFlag->particlesWide; j++ )
        {
            // pin the corners
            if(myFlag->particles[i][j]->pinned)
            {
                // set velocity to zero
                myFlag->particles[i][j]->velocity.x=0.0;
                myFlag->particles[i][j]->velocity.y=0.0;
                myFlag->particles[i][j]->velocity.z=0.0;

                continue;   // skip euler for this particle
            }

            // check for collision with ball
            else if( collidesWithBall(myFlag->particles[i][j]) )
            {
                // set velocity to zero
                myFlag->particles[i][j]->velocity.x=0.0;
                myFlag->particles[i][j]->velocity.y=0.0;
                myFlag->particles[i][j]->velocity.z=0.0;

                continue;   // skip euler for this particle
            }

            // update all other particles
            else
            {
                // calculate acceleration: a = F/m where m=1
                a = myFlag->particles[i][j]->force;

                // get velocity of spring
                v = myFlag->particles[i][j]->velocity;

                // update velocity
                v = v + dt*a;
                myFlag->particles[i][j]->velocity = v;

                // get position of spring
                x = myFlag->particles[i][j]->position;

                // check for collisision with ball
                /*if( collidesWithBall(myFlag->particles[i][j]) )
                {
                    //x = ;   // bump particle back to ball's circumference
                    //myFlag->particles[i][j]->position = x;
                    continue;   // skip remaining updates
                }*/

                // update position
                x = x + v*dt;
                myFlag->particles[i][j]->position = x;
            }
        }

    }

}


// Runge Kutta simulation step
void Sim::rungeKuttaStep(float dt)
{
    int i,j;
    float h,x,v,a,k1,k2,k3,k4;
    h = dt;

    /*for(i=0; i<myFlag->springsHigh; i++)
    {
        for(j=0; j<myFlag->springsWide; j++)
        {
            // K1
            a = acceleration(myFlag->springs[i][j]);
            v = myFlag->springs[i][j]->xVelocity;
            v += a*dt;
            k1 = h * v;

            // K2
            a = acceleration(myFlag->springs[i][j]);
            // ...etc

        }
    }*/
}


// set acceleration of thisParticle
float Sim::acceleration(Particle *thisParticle)
{
    // get length of spring
    /*vec3 length =  subtract(thisParticle->position, thisParticle->xCoordWall;

    // limit stretch of spring
    if( length > 2.0*thisParticle->restLength )
    {
        length = 2.0* thisParticle->restLength;
    } else if( length < -2.0*thisParticle->restLength )
    {
        length = -2.0 * thisParticle->restLength;
    }

    // calculate acceleration
    float x = length - thisParticle->restLength;
    float v = thisParticle->xVelocity;
    float k = thisParticle->springConstant;
    float c = thisParticle->dampingConstant;
    float m = thisParticle->mass;
    float a = -1.0*(k*x + c*v)/m;

    // return acceleration
    return a;*/

    return 0.0;

}


// Update forces on all particles
void Sim::updateForces()
{
    int i,j;
    glm::vec3 force, v;

    // Reset forces
    for( i=0; i<myFlag->particlesHigh; i++ )
    {
        for( j=0; j<myFlag->particlesWide; j++ )
        {
            // reset spring force for next calculation
            myFlag->particles[i][j]->springForce.x = 0.0f;
            myFlag->particles[i][j]->springForce.y = 0.0f;
            myFlag->particles[i][j]->springForce.z = 0.0f;

            // add dampening force externally
            v = myFlag->particles[i][j]->velocity;
            myFlag->particles[i][j]->externalForce = myFlag->particles[i][j]->gravityForce - v * myFlag->dampingConstant
                    //+ 0.1f*vec3(myFlag->particles[i][j]->position.x*abs(sin(t/10)), 0, 0);   // wind for flag
                    + vec3(5*abs(sin(t/6)), 0, 0);

        }
    }

    // Add on current spring forces
    for( i=0; i<myFlag->implementedSprings; i++ )
    {
        // get current spring force
        force = myFlag->springs[i]->force();

        // add current spring force to end particles
        myFlag->springs[i]->particle1->springForce += force;
        myFlag->springs[i]->particle2->springForce -= force;

    }

    // Update total forces on particles
    for( i=0; i<myFlag->particlesHigh; i++ )
    {
        for( j=0; j<myFlag->particlesWide; j++ )
        {
            // F = Fext + Fspring
            myFlag->particles[i][j]->force = myFlag->particles[i][j]->externalForce + myFlag->particles[i][j]->springForce;
        }
    }
}

// Check for collision of one particle with ball
bool Sim::collidesWithBall(Particle * thisParticle)
{
    // find distance from ball's origin
    vec3 distanceVector = thisParticle->position - myBall->origin;
    float distance = length(distanceVector);

    if( distance < myBall->radius * 1.01f )
    {
        // push particle back to ball's circumference
        vec3 x = myBall->origin + normalize(distanceVector) * myBall->radius * 1.01f;
        thisParticle->position = x;

        // collision detected
        return true;
    }

    // no collision detected
    return false;
}
