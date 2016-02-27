#include "ball.h"

#include "foundation.h"

// Constructor
Ball::Ball()
{
    radius = 100.0f;
    origin = vec3(300.0f, 405.0f, 0.0f);
}

// Destructor
Ball::~Ball()
{

}

// Draw function
void Ball::draw()
{
    // get the coordinates and radius
    float x = origin.x;
    float y = origin.y;
    float resolution = 20.0f;

    // Compute angle of each triangle in fan
    float theta = 2.0f * PI / resolution;

    glColor3f(0.1,0.3,0.6);
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
