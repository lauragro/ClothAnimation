#include "sim.h"
#include "foundation.h"

// Constructor
Sim::Sim()
{
    cout << "Simulator Initialization\n";

    //myBall = new Ball(0);

    //myGround = new Ground(myBall->origin.y + myBall->radius);

    myPerson = new Person();
    myFlag = new Flag(0);
    t = 0;

}

// Destructor
Sim::~Sim()
{
    cout << "Simulator Destruction\n";
    delete myFlag;
}

// Draw everything on screen
void Sim::draw(GLuint * textures)
{
    // Draw ground
    //myGround->draw(textures[0]);


    // Draw blue circles
    for( int i=0; i<myFlag->particlesHigh; i++ )
    {
        for(int j=0; j<myFlag->particlesWide; j++)
        {
            myFlag->particles[i][j]->draw();
        }
    }

    // Draw ball
    //myBall->draw(textures[1]);

    myPerson->draw(textures[1],textures[1]);

    // Draw connecting lines
    for( int i=0; i<myFlag->implementedSprings; i++ )
    {
        myFlag->springs[i]->draw();
    }

}

// Simulation step using interpolation
void Sim::simStep()
{
    int type = 1;
    float dt = 0.1f;//2f;
    t += dt;

    switch (type)
    {
        case 0:
            rightStep(dt);
            break;
        case 1:
            eulerStep(dt);
            break;
        default://case 2:
            //rungeKuttaStep(dt); // This fails after multiple collisions!
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

    // move ball when cloth is in sheet mode
    //if( myFlag->type == SHEET )
    //{
        //myBall->origin += vec3(0, -sin(t/12), 0);

    //}

    // update forces on particles
    updateForces(0);

    // update velocities and positions of particles
    for( i=0; i<myFlag->particlesHigh; i++ )
    {
        for( j=0; j<myFlag->particlesWide; j++ )
        {
            // pin the corners
            if(myFlag->particles[i][j]->pinned)
            {
                // set velocity to zero
                myFlag->particles[i][j]->velocity=vec3(0.0f,0.0f,0.0f);

                continue;

            // adjust for collision with person
            } else if(myPerson->collidesWith(myFlag->particles[i][j])){

                // set velocity to zero
                myFlag->particles[i][j]->velocity=vec3(0.0f,0.0f,0.0f);

                continue;

            // update all other particles
            }
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

                // update position
                x = x + v*dt;// + 0.5f * a * dt * dt;
                myFlag->particles[i][j]->position = x;
            }
        }

    }

}


// Runge Kutta 4th Order simulation step
/*void Sim::rungeKuttaStep(float dt)
{
    vec3 x,v, dx1, dx2, dx3, dx4, dv1, dv2, dv3, dv4;
    int i,j;

    // Step 1
    updateForces(0);
    for(i=0; i<myFlag->particlesHigh; i++)
    {
        for(j=0; j<myFlag->particlesWide; j++)
        {
            // pin the corners and detect collisions
            if(myFlag->particles[i][j]->pinned
                    || collidesWithBall(myFlag->particles[i][j],0) || collidesWithGround(myFlag->particles[i][j],0))
            {
                // set velocity to zero
                myFlag->particles[i][j]->velocity=vec3(0.0f,0.0f,0.0f);
                myFlag->particles[i][j]->velocity1=vec3(0.0f,0.0f,0.0f);
                myFlag->particles[i][j]->velocity2=vec3(0.0f,0.0f,0.0f);
                myFlag->particles[i][j]->velocity3=vec3(0.0f,0.0f,0.0f);

                continue;   // skip euler for this particle
            }

            // update all other particles
            else
            {
                // capture current position and velocity
                x = myFlag->particles[i][j]->position;
                v = myFlag->particles[i][j]->velocity;

                // calculate RK4 values
                dx1 = dt * v;
                dv1 = dt * myFlag->particles[i][j]->force;  //acceleration(x,T);

                // store intermediate values
                myFlag->particles[i][j]->position1 = x + dx1/2.0f;
                myFlag->particles[i][j]->velocity1 = v + dv1/2.0f;
            }
        }
    }

    // Step 2
    updateForces(1);
    for(i=0; i<myFlag->particlesHigh; i++)
    {
        for(j=0; j<myFlag->particlesWide; j++)
        {
            // pin the corners and check for collisions
            if(myFlag->particles[i][j]->pinned
                    || collidesWithBall(myFlag->particles[i][j],1) || collidesWithGround(myFlag->particles[i][j],1))
            {
                // set velocity to zero
                myFlag->particles[i][j]->velocity=vec3(0.0f,0.0f,0.0f);
                myFlag->particles[i][j]->velocity1=vec3(0.0f,0.0f,0.0f);
                myFlag->particles[i][j]->velocity2=vec3(0.0f,0.0f,0.0f);
                myFlag->particles[i][j]->velocity3=vec3(0.0f,0.0f,0.0f);

                continue;   // skip euler for this particle
            }

            // update all other particles
            else
            {
                // capture current position and velocity
                x = myFlag->particles[i][j]->position;
                v = myFlag->particles[i][j]->velocity;

                // calculate RK4 values
                dx2 = dt * (v + dv1/2.0f);
                dv2 = dt * myFlag->particles[i][j]->force;  //acceleration(x + dx1/2.0f, T + dt/2.0f);

                // store intermediate values
                myFlag->particles[i][j]->position2 = x + dx2/2.0f;
                myFlag->particles[i][j]->velocity2 = v + dv2/2.0f;
            }
        }
    }

    // Step 3
    updateForces(2);
    for(i=0; i<myFlag->particlesHigh; i++)
    {
        for(j=0; j<myFlag->particlesWide; j++)
        {
            // pin the corners and check for collisions
            if(myFlag->particles[i][j]->pinned
                    || collidesWithBall(myFlag->particles[i][j],2) || collidesWithGround(myFlag->particles[i][j],2))
            {
                // set velocity to zero
                myFlag->particles[i][j]->velocity=vec3(0.0f,0.0f,0.0f);
                myFlag->particles[i][j]->velocity1=vec3(0.0f,0.0f,0.0f);
                myFlag->particles[i][j]->velocity2=vec3(0.0f,0.0f,0.0f);
                myFlag->particles[i][j]->velocity3=vec3(0.0f,0.0f,0.0f);

                continue;   // skip euler for this particle
            }

            // update all other particles
            else
            {
                // capture current position and velocity
                x = myFlag->particles[i][j]->position;
                v = myFlag->particles[i][j]->velocity;

                // calculate RK4 values
                dx3 = dt * (v + dv2/2.0f);
                dv3 = dt *  myFlag->particles[i][j]->force;    //acceleration(x + dx2/2.0f, T + dt/2.0f);

                // store intermediate values
                myFlag->particles[i][j]->position3 = x + dx3;
                myFlag->particles[i][j]->velocity3 = v + dv3;
            }
        }
    }

    // Step 4
    updateForces(3);
    for(i=0; i<myFlag->particlesHigh; i++)
    {
        for(j=0; j<myFlag->particlesWide; j++)
        {
            // pin the corners and check for collisions
            if(myFlag->particles[i][j]->pinned
                    || collidesWithBall(myFlag->particles[i][j],3) || collidesWithGround(myFlag->particles[i][j],3))
            {
                // set velocity to zero
                myFlag->particles[i][j]->velocity=vec3(0.0f,0.0f,0.0f);
                myFlag->particles[i][j]->velocity1=vec3(0.0f,0.0f,0.0f);
                myFlag->particles[i][j]->velocity2=vec3(0.0f,0.0f,0.0f);
                myFlag->particles[i][j]->velocity3=vec3(0.0f,0.0f,0.0f);

                continue;   // skip euler for this particle
            }

            // update all other particles
            else
            {
                // capture current position and velocity
                x = myFlag->particles[i][j]->position;
                v = myFlag->particles[i][j]->velocity;

                // calculate RK4 values
                dx4 = dt * (v + dv3);
                dv4 = dt * myFlag->particles[i][j]->force;    // acceleration(x + dx3, T + dt);

                // update final positions and velocities
                myFlag->particles[i][j]->position = x + dx1/6.0f + dx2/3.0f + dx3/3.0f + dx4/6.0f;
                myFlag->particles[i][j]->velocity = v + dv1/6.0f + dv2/3.0f + dv3/3.0f + dv4/6.0f;
            }
        }
    }
}*/


// Update forces on all particles
void Sim::updateForces(int number)
{
    int i,j;
    glm::vec3 force, v, normalForce;

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
            switch(number){
            case 0:
                v = myFlag->particles[i][j]->velocity;
                break;
            case 1:
                v = myFlag->particles[i][j]->velocity1;
                break;
            case 2:
                v = myFlag->particles[i][j]->velocity2;
                break;
            default://case 3:
                v = myFlag->particles[i][j]->velocity3;
                //break;
            }

            // TODO: add wind
            myFlag->particles[i][j]->externalForce = myFlag->particles[i][j]->gravityForce - v * myFlag->dampingConstant;

        }
    }

    // Add on current spring forces
    for( i=0; i<myFlag->implementedSprings; i++ )
    {
        // get current spring force
        force = myFlag->springs[i]->force(number);

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

            if(myPerson->collidesWith(myFlag->particles[i][j]))
            {
                // compute the response force
                normalForce = normalize(myFlag->particles[i][j]->position - myPerson->head->origin)
                        * dot(myFlag->particles[i][j]->force, normalize(myFlag->particles[i][j]->position - myPerson->head->origin));
                myFlag->particles[i][j]->force -= normalForce;
            }

            /*if(collidesWithGround(myFlag->particles[i][j],0))
            {
                // compute the response force   DOESNT WORK YET!!!!!!
                normalForce = myGround->topNormal * dot(myFlag->particles[i][j]->force, myGround->topNormal);
                myFlag->particles[i][j]->force += normalForce;
            }*/

        }

    }

}


// Check for collision of one particle with ground
/*bool Sim::collidesWithGround(Particle * thisParticle, int number)
{
    // particle coords
    float x,y,z;
    switch(number){
    case 0:
        x = thisParticle->position.x;
        y = thisParticle->position.y;
        z = thisParticle->position.z;
        break;
    case 1:
        x = thisParticle->position1.x;
        y = thisParticle->position1.y;
        z = thisParticle->position1.z;
        break;
    case 2:
        x = thisParticle->position2.x;
        y = thisParticle->position2.y;
        z = thisParticle->position2.z;
        break;
    default://case 3:
        x = thisParticle->position3.x;
        y = thisParticle->position3.y;
        z = thisParticle->position3.z;
        //break;
    }

    // ground coords
    float ymin = myGround->ymin;
    float ymax = myGround->ymax;
    float xmin = myGround->xmin;
    float xmax = myGround->xmax;
    float zmin = myGround->zmin;
    float zmax = myGround->zmax;

    // collides with block
    if(     y >= ymin
         /*&& y <= ymax
         && x >= xmin
         && x <= xmax
         && z >= zmin
         && z <= zmax   )
    {*/
        // push particle back
        /*switch(number){
        case 0:
            thisParticle->position.y = ymin;
            break;
        case 1:
            thisParticle->position1.y = ymin;
            break;
        case 2:
            thisParticle->position2.y = ymin;
            break;
        default://case 3:
            thisParticle->position3.y = ymin;
            //break;
        }

        // collision detected
        return true;
    }

    // no collision detected
    return false;
}*/