#include "flag.h"

Flag::Flag(int zCentre)
{
    // Attributes
    height = 900.0;//600.0;//300.0;
    width = 900.0;//450.0;
    particleMass = 1.0;
    //springConstant = 100.0;
    dampingConstant = 0.4f;

    if(type == SHEET)
    {
        createSheet(zCentre);
    } else if(type == BLANKET)
    {
        createBlanket(zCentre);
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
            if( j<particlesWide-2 )
            {
                // Horizontal bend spring
                springs[springIndex] = new Spring(particles[i][j], particles[i][j+2], 2);
                springIndex++;
            }
            if( i<particlesHigh-2 )
            {
                // Verticle bend spring
                springs[springIndex] = new Spring(particles[i][j], particles[i+2][j], 2);
                springIndex++;
            }

        }

        if( i<particlesHigh-1 )
        {
            // Vertical structural spring
            springs[springIndex] = new Spring(particles[i][particlesWide-1], particles[i+1][particlesWide-1], 0);
            springIndex++;
        }

        if( i<particlesHigh-2 )
        {
            // Vertical bend spring
            springs[springIndex] = new Spring(particles[i][particlesWide-1], particles[i+2][particlesWide-1], 2);
            springIndex++;
        }


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


/* Construct all particles for a vertically hanging sheet */
void Flag::createSheet(int zCentre)
{
    float x,y,z;
    z=zCentre; // camera points in -z direction

    // positions of corners
    int top = 0;
    int bottom = particlesHigh-1;
    int left = 1;
    int right = particlesWide-2;


    y = 0;
    x = 0;

    // Particles
    for(int i=0; i<particlesHigh; i++)
    {
        // y coord
        y = height/particlesHigh*(i+1) - height*1.4;
        //y += height/particlesHigh;

        for(int j=0; j<particlesWide; j++)
        {
            // x coord
            x = width/particlesWide*(j+1) - width/2;
            //x += width/particlesWide;

            // create particle
            particles[i][j] = new Particle(x,y,z);

        }

    }

    // Pin the corners
    particles[top][left]->pinned = true;
    particles[top][right]->pinned = true;
}


/* Construct all particles for a horizontally lying blanket */
void Flag::createBlanket(int zCentre)
{
    float x,y,z;
    y = -200.0;   // just a bit below the top of the screen

    float halfWidth = (float)width/2.0f;
    float halfHeight = (float)height/2.0f;

    // Particles
    for(int i=0; i<particlesHigh; i++)
    {
        // z coord
        z = zCentre - height/particlesHigh*(i+1) + halfHeight;

        for(int j=0; j<particlesWide; j++)
        {
            // x coord
            x = width/particlesWide*(j+1) - halfWidth;

            // create particle
            particles[i][j] = new Particle(x,y,z);
        }
    }

    // don't pin anything yet
}
