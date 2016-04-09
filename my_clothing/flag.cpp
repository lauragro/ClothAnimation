#include "flag.h"

Flag::Flag(int zCentre)
{
    // Attributes
    height = 1200.0f;//900.0;//600.0;//300.0;
    width = 1200.0f;//900.0;//450.0;
    particleMass = 1.0;
    dampingConstant = 1.0f;

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
    y = -450.0;   // just a bit below the top of the screen

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

/* Calculate the triangle normal between three particles */
vec3 Flag::calcTriangleNormal(Particle *p1,Particle *p2,Particle *p3)
{
    vec3 pos1 = p1->position;
    vec3 pos2 = p2->position;
    vec3 pos3 = p3->position;

    vec3 v1 = pos2-pos1;
    vec3 v2 = pos3-pos1;

    return cross(v1, v2);
}

/* Draw a single triangle with shading */
void Flag::drawTriangle(Particle *p1, Particle *p2, Particle *p3, const vec3 colour)
{
    vec3 norm;

    glColor3fv( (GLfloat*) &colour );

    norm = normalize(p3->normal);
    glNormal3fv((GLfloat *) &norm);
    glVertex3fv((GLfloat *) &(p3->position ));

    norm = normalize(p2->normal);
    glNormal3fv((GLfloat *) &norm);
    glVertex3fv((GLfloat *) &(p2->position ));

    norm = normalize(p1->normal);   // must normalize each particle's "normal" as they are not of unit length.
    glNormal3fv((GLfloat *) &norm);
    glVertex3fv((GLfloat *) &(p1->position ));




}

/* Draw flag with shaders */
void Flag::draw()
{
    int i,j;
    vec3 normal,colour;

    // reset normals (which where written to last frame)
    for(i=0; i<particlesHigh; i++)
    {
        for (j=0; j<particlesWide; j++)
        {
            particles[i][j]->normal = vec3(0.0f,0.0f,0.0f);
        }

    }

    //create smooth per particle normals by adding up all the (hard) triangle normals that each particle is part of
    for( i=0; i<particlesHigh-1; i++)
    //for(int x = 0; x<num_particles_width-1; x++)
    {
        for( j=0; j<particlesWide-1; j++)
        //for(int y=0; y<num_particles_height-1; y++)
        {
            normal = calcTriangleNormal(    particles[i+1][j],//getParticle(x+1,y),
                                            particles[i][j],//getParticle(x,y),
                                            particles[i][j+1]);//getParticle(x,y+1));
            particles[i+1][j]->normal += normal;
            particles[i][j]->normal += normal;
            particles[i][j+1]->normal += normal;

            normal = calcTriangleNormal(    particles[i+1][j+1],//getParticle(x+1,y+1),
                                            particles[i+1][j],//getParticle(x+1,y),
                                            particles[i][j+1]);//getParticle(x,y+1));
            particles[i+1][j+1]->normal += normal;
            particles[i+1][j]->normal += normal;
            particles[i][j+1]->normal += normal;
        }
    }

    glBegin(GL_TRIANGLES);
    for( i=0; i<particlesHigh-1; i++ )
    //for(int x = 0; x<num_particles_width-1; x++)
    {
        for( j=0; j<particlesWide-1; j++)
        //for(int y=0; y<num_particles_height-1; y++)
        {
            //vec3 colour = vec3(0.0f,0.0f,0.0f);
            if (i%2 == 0)
            {
                // red and white color is interleaved according to which column number
                colour = vec3(0.6f,0.2f,0.2f);
            } else
            {
                colour = vec3(1.0f,1.0f,0.0f);
            }

            drawTriangle(particles[i+1][j], //getParticle(x+1,y),
                        particles[i][j],    //getParticle(x,y),
                        particles[i][j+1],colour);//getParticle(x,y+1),colour);
            drawTriangle(particles[i+1][j+1],//getParticle(x+1,y+1),
                        particles[i+1][j],  //getParticle(x+1,y),
                        particles[i][j+1],colour);//getParticle(x,y+1),colour);
        }
    }
    glEnd();
}




