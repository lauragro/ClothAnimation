#include "camera.h"
#include <float.h>

// Constructor
Camera::Camera()
{

}

// Destructor
Camera::~Camera()
{
    cout << "camera destruction" << endl;
}

void Camera::startup(float winw, float winh)
{
    /*this->winw = winw;  // capture properties passed in from widget
    this->winh = winh;

    xangle= yangle= zangle=0.0;*/
    //scale = 1.0;
    dolly_factor = 1.0;
    CameraPos.x = 1;
    CameraPos.y = 1;
    CameraPos.z = 100;
    /*Rotating = false;
    Scaling = false;*/

    /* Testing */
    cout << "camera thinks width is " << winw << endl;
    cout << "camera thinks height is " << winh << endl;

    //===========Camera stuff from Lucky and 305 assignment===========
        vppos_x = 0;
        vppos_y = 0;

        camera_phi = PI/2;
        camera_phi_speed = 0;
        camera_theta = 0;
        camera_theta_speed = 0;

        dolly_factor = 5;
        left_pressed = false;
        right_pressed = false;
    //================================================================
}




//=====================Functions from Lucky and 305 assignment======
void Camera::MouseMove(double x, double y)
{
   vppos_x = (float)(x) / 256 - 1;
   vppos_y = 1 - (float)(y) / 256;

   if (left_pressed)
   {
      camera_theta_speed = (float)(x - lastX) * - 0.01f; //?
      camera_phi_speed = (float)(y - lastY) * 0.01f;
   }

   if (right_pressed)
   {
      dolly_factor += (y - lastY);// * 0.1f;
      if (dolly_factor < 1) dolly_factor = 1;
      //if (dolly_factor < -100) dolly_factor = -100;
      if (dolly_factor > 100) dolly_factor = 100;

      // dolly
      //CameraPos *= glm::mix( CameraPos, dolly_factor * CameraPos, 0.1 );

   }

   lastX = x;
   lastY = y;
}

void Camera::MouseButton(QMouseEvent *e, bool press)
{
    if (e->button() == Qt::LeftButton)
    {
        if (press == true)
        {
            lastX = e->x();
            lastY = e->y();
            left_pressed = true;
        }
        else left_pressed = false;
    };

    if (e->button() == Qt::RightButton)
    {
        if (press == true)
        {
            lastX = e->x();
            lastY = e->y();
            right_pressed = true;
        }
        else right_pressed = false;
    };
}

void Camera::updatePos()
{
    CameraPos.x = dolly_factor * sin(camera_phi) * sin(camera_theta);
    CameraPos.y = dolly_factor * cos(camera_phi);
    CameraPos.z = dolly_factor * sin(camera_phi) * cos(camera_theta);

    //CameraPos = mat3(dolly_factor) * CameraPos * ;
    //CameraPos = glm::mix(CameraPos, CameraPos, CameraPos*dolly_factor);

    // Set ModelViewMatrix
        /*glm::mat4 identity        = glm::mat4(1.0); // Start with the identity as the transformation matrix
        glm::mat4 pointTranslateZ = glm::mix(identity, glm::vec3(0.0f, 0.0f, -dolly_factor),1.0f); // Zoom in or out by translating in z-direction based on user input
      glm::mat4 viewRotateX     = glm::rotate(pointTranslateZ, rotate_x, glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate the whole scene in x-direction based on user input
        glm::mat4 viewRotateY     = glm::rotate(viewRotateX,  rotate_y, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate the whole scene in y-direction based on user input
        glm::mat4 pointRotateX    = glm::rotate(viewRotateY, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate the camera by 90 degrees in negative x-direction to get a frontal look on the szene
      glm::mat4 viewTranslate   = glm::mix(pointTranslateZ, glm::vec3(-dimensionX/2.0f, -dimensionY/2.0f, -dimensionZ/2.0f), 1.0f); // Translate the origin to be the center of the cube
        M_cam = viewTranslate;*/

}
//==================================================================
