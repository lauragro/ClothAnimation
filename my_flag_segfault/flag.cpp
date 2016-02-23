#include "flag.h"

Flag::Flag()
{
    // Attributes
    height = 300.0;
    width = 450.0;
    particleMass = 1.0;
    springConstant = 200.0;
    dampingConstant = 100.0;

    double x,y,z;
    z=0.0;

    // positions of corners
    int top = 0;
    int bottom = particlesHigh-1;
    int left = 1;
    int right = particlesWide-2;


    // Particles
    for(int i=0; i<particlesHigh; i++)
    {
        // y coord
        y = height/particlesHigh*(i+1);

        for(int j=0; j<particlesWide; j++)
        {
            // x coord
            x = width/particlesWide*(j+1);

            // create particle
            particles[i][j] = new Particle(x,y,z);

            // add gravity
            particles[i][j]->externalForce = new Vector3D(0,9.81,0);
            particles[i][j]->force = particles[i][j]->externalForce;

        }

    }

    // Pin the corners
    particles[top][left]->pinned = true;
    particles[top][right]->pinned = true;

    // Springs
    int springIndex=0;
    for( int i=0; i<particlesHigh; i++ )
    {
        for( int j=0; j<particlesWide-1; j++ )
        {
            // Horizontal structural spring
            springs[springIndex] = new Spring(particles[i][j], particles[i][j+1], 0);
            springIndex++;

            if( i<particlesHigh-1 )
            {
                // Vertical structural spring
                springs[springIndex] = new Spring(particles[i][j], particles[i+1][j], 0);
                springIndex++;

                // Backslash shear spring
                springs[springIndex] = new Spring(particles[i][j], particles[i+1][j+1], 1);
                springIndex++;
            }
            if( i>0 )
            {
                // Forwardslash shear spring
                springs[springIndex] = new Spring(particles[i][j], particles[i-1][j+1], 1);
                springIndex++;
            }
            /*if( j<particlesWide-2 )
            {
                // Horizontal bend spring
                springs[springIndex] = new Spring(particles[i][j], particles[i][j+2], 2);
                springs[springIndex]->springConstant = 20.0;
                springIndex++;
            }
            if( i<particlesHigh-2 )
            {
                // Verticle bend spring
                springs[springIndex] = new Spring(particles[i][j], particles[i+2][j], 2);
                springs[springIndex]->springConstant = 20.0;
                springIndex++;
            }*/

        }

        if( i<particlesHigh-1 )
        {
            // Vertical structural spring
            springs[springIndex] = new Spring(particles[i][particlesWide-1], particles[i+1][particlesWide-1], 0);
            springIndex++;
        }

        /*if( i<particlesHigh-2 )
        {
            // Vertical bend spring
            springs[springIndex] = new Spring(particles[i][particlesWide-1], particles[i+2][particlesWide-1], 2);
            springs[springIndex]->springConstant = 20.0;
            springIndex++;
        }*/

    }
    implementedSprings = springIndex;
}

Flag::~Flag()
{
    cout << "Flag Destruction\n";

    int i,j;
    // delete all springs from memory
    for( i=0; i<implementedSprings; i++ )
    {
        delete springs[i];
    }

    // delete all particles from memory
    for( i = 0; i<particlesHigh; i++ )
        for( j=0; j<particlesWide; j++ )
        {
            delete particles[i][j];
        }
}
