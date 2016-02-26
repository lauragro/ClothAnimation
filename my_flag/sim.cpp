#include "sim.h"

// Constructor
Sim::Sim()
{
    cout << "Simulator Initialization\n";

    myFlag = new Flag();

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
    for( int i=0; i<myFlag->particlesHigh; i++ )
    {
        for(int j=0; j<myFlag->particlesWide; j++)
        {
            myFlag->particles[i][j]->draw();
        }
    }

    // Draw connecting lines
    for( int i=0; i<myFlag->implementedSprings; i++ )
    {
        myFlag->springs[i]->draw();
    }


    //cout << "x coord = " << myFlag->springs[0]->xCoord << endl;
    //cout << "y coord = " << myFlag->springs[0]->yCoord << endl;

}

// Simulation step using interpolation
void Sim::simStep()
{
    int type = 1;
    double dt = 0.1;

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
void Sim::rightStep(double dt)
{
    for(int i=0; i<myFlag->particlesHigh; i++)
    {
        for(int j=0; j<myFlag->particlesWide; j++)
        {
            myFlag->particles[i][j]->position->x += 10;
        }
    }
}

// Euler simulation step
void Sim::eulerStep(double dt)
{
    int i,j;
    Vector3D *x, *v, *a;

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
                myFlag->particles[i][j]->velocity->x=0.0;
                myFlag->particles[i][j]->velocity->y=0.0;
                myFlag->particles[i][j]->velocity->z=0.0;

                continue;   // skip euler for this particle
            }
            // update all other particles
            else
            {
                // a = F/m
                a = a->scaleDown(myFlag->particles[i][j]->force, myFlag->particles[i][j]->mass);

                // get velocity of spring
                v = myFlag->particles[i][j]->velocity;

                // v = v + a*dt
                v = v->add(v, v->scaleUp(a,dt));
                myFlag->particles[i][j]->velocity = v;

                // get position of spring
                x = myFlag->particles[i][j]->position;

                // x = x + v * dt;
                x = x->add(x, x->scaleUp(v, dt));
                *myFlag->particles[i][j]->position = *x;
            }
        }

    }

}


// Runge Kutta simulation step
void Sim::rungeKuttaStep(double dt)
{
    int i,j;
    double h,x,v,a,k1,k2,k3,k4;
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
double Sim::acceleration(Particle *thisParticle)
{
    // get length of spring
    /*Vector3D length =  subtract(thisParticle->position, thisParticle->xCoordWall;

    // limit stretch of spring
    if( length > 2.0*thisParticle->restLength )
    {
        length = 2.0* thisParticle->restLength;
    } else if( length < -2.0*thisParticle->restLength )
    {
        length = -2.0 * thisParticle->restLength;
    }

    // calculate acceleration
    double x = length - thisParticle->restLength;
    double v = thisParticle->xVelocity;
    double k = thisParticle->springConstant;
    double c = thisParticle->dampingConstant;
    double m = thisParticle->mass;
    double a = -1.0*(k*x + c*v)/m;

    // return acceleration
    return a;*/

    return 0.0;

}


// Update forces on all particles
void Sim::updateForces()
{
    int i,j;
    Vector3D *force, *v;

    // Reset forces
    for( i=0; i<myFlag->particlesHigh; i++ )
    {
        for( j=0; j<myFlag->particlesWide; j++ )
        {
            // reset spring force for next calculation
            myFlag->particles[i][j]->springForce->x = 0;
            myFlag->particles[i][j]->springForce->y = 0;
            myFlag->particles[i][j]->springForce->z = 0;

            // add dampening force externally
            //v = myFlag->particles[i][j]->velocity;
            //myFlag->particles[i][j]->externalForce = v->subtract(myFlag->particles[i][j]->gravityForce, v->scaleUp(v, myFlag->dampingConstant));
        }
    }

    // Add on current spring forces
    for( i=0; i<myFlag->implementedSprings; i++ )
    {
        // get current spring force
        force = myFlag->springs[i]->force();

        // add current spring force to end particles
        myFlag->springs[i]->particle1->springForce = v->add(myFlag->springs[i]->particle1->springForce, force);
        myFlag->springs[i]->particle2->springForce = v->subtract(myFlag->springs[i]->particle2->springForce,force);

    }

    // Update total forces on particles
    for( i=0; i<myFlag->particlesHigh; i++ )
    {
        for( j=0; j<myFlag->particlesWide; j++ )
        {
            // F = Fext + Fspring
            myFlag->particles[i][j]->force = v->add(myFlag->particles[i][j]->gravityForce, myFlag->particles[i][j]->springForce);

        }
    }
}
