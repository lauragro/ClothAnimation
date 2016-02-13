#include "flag.h"

Flag::Flag()
{
    // Attributes
    height = 300.0;
    width = 450.0;
    particleMass = 1.0;
    springConstant = 1.0;
    dampingConstant = 0.8;

    double x,y,z;
    z=0.0;

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
        }

        if( i<particlesHigh-1 )
        {
            // Vertical structural spring
            springs[springIndex] = new Spring(particles[i][particlesWide-1], particles[i+1][particlesWide-1], 0);
            springIndex++;
        }

    }
    implementedSprings = springIndex;
}

Flag::~Flag()
{
    cout << "Flag Destruction\n";
}
