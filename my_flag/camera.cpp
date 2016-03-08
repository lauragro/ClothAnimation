#include "camera.h"
#include <float.h>

//typedef glm::mat3;

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
    this->winw = winw;  // capture properties passed in from widget
    this->winh = winh;

    xangle= yangle= zangle=0.0;
    scale = 1.0;
    CameraPos.x = 1;
    CameraPos.y = 1;
    CameraPos.z = 100;
    Rotating = false;
    Scaling = false;

    /* Testing */
    cout << "camera thinks width is " << winw << endl;
    cout << "camera thinks height is " << winh << endl;

    //===========Camera stuff from Lucky and 305 assignment===========
        //width = 512;    // not used
        //height = 512;   // not used

        vppos_x = 0;
        vppos_y = 0;

        camera_phi = PI/2;
        camera_phi_speed = 0;
        camera_theta = 0;
        camera_theta_speed = 0;

        camera_radius = 5;
        left_pressed = false;
        right_pressed = false;
    //================================================================
}

// Handle the mouse being pressed
void Camera::mousePressEvent(QMouseEvent *e)
{
    // Commenting out to switch to Lucky's way

    // Get mouse location
    /*QPoint MouseLocation = e->pos();

    // Change y coord to be relative
    MouseLocation.setY(height() - e->y());

    // Left mouse button pressed: rotate view
    if (e->button() == Qt::LeftButton)
    {
        Rotating = true;
        lastMousePoint = e->pos();
    }

    // Right mouse button pressed: zoom view
    if (e->button() == Qt::RightButton)
    {
        lastMousePoint = e->pos();
        Scaling = true;
    }*/
}

// Handle the mouse being released
void Camera::mouseReleaseEvent(QMouseEvent *e)
{
    // Commenting out to switch to Lucky's way

    // Left button released when in rotate mode
    /*if (e->button() == Qt::LeftButton && Rotating)
    {
        DoRotate(e->pos(), lastMousePoint);
        Rotating = false;
    }

    // Right button released when in scale mode
    if (e->button() == Qt::RightButton && Scaling)
    {
        DoScale(e->pos(), lastMousePoint);
        Scaling = false;
    }*/

}

// Handle the mouse being moved
void Camera::mouseMoveEvent(QMouseEvent *e)
{
    // Commenting out to switch to Lucky's way

    // Left button moved when in rotate mode
    /*if ((e->buttons() & Qt::LeftButton) && Rotating)
    {
        DoRotate(e->pos(), lastMousePoint);
        lastMousePoint = e->pos();
    }

    // Right button moved when in scale mode
    if ((e->buttons() & Qt::RightButton) && Scaling)
    {
        DoScale(e->pos(), lastMousePoint);
        lastMousePoint = e->pos();
    }*/

}

// Rotate camera in y
void Camera::RotateY(float rad)
{
    // compute trig
    float cosPhi = (float)cos(rad);
    float sinPhi = (float)sin(rad);

    // define all values of matrix
    m11 = cosPhi;   //m11
    m12 = 0.0f;     //m12
    m13 = sinPhi;   //m13
    m21 = 0.0f;     //m21
    m22 = 1.0f;     //m22
    m23 = 0.0f;     //m23
    m31 = - sinPhi; //m31
    m32 = 0.0f;     //m32
    m33 = cosPhi;   //m33


    // put values in a matrix
    vec3 col1 = vec3(m11,m21,m31);
    vec3 col2 = vec3(m12,m22,m32);
    vec3 col3 = vec3(m13,m23,m33);
    mat3 matrix = mat3(col1, col2, col3);

    CameraPos = matrix * CameraPos;   // comment out for testing

}

/* ACTUALLY ROTATE X - SHOULD CHANGE NAME */
// Rotate camera in z
void Camera::RotateZ(float rad)
{
    // compute trig
    float cosPhi = (float)cos(rad);
    float sinPhi = (float)sin(rad);

    // define all values of Matrix Z
    m11 = cosPhi;   //m11
    m12 = - sinPhi; //m12
    m13 = 0.0f;     //m13
    m21 = sinPhi;   //m21
    m22 = cosPhi;   //m22
    m23 = 0.0f;     //m23
    m31 = 0.0f;     //m31
    m32 = 0.0f;     //m32
    m33 = 1.0f;     //m33

    // Matrix X
    /*m11 = 0.0;
    m12 = cosPhi;
    m13 = -sinPhi;
    m21 = 0.0;
    m22 = sinPhi;
    m23 = cosPhi;
    m31 = 1.0;
    m32 = 0.0;
    m33 = 0.0;*/

    // put values in a matrix
    vec3 col1 = vec3(m11,m21,m31);
    vec3 col2 = vec3(m12,m22,m32);
    vec3 col3 = vec3(m13,m23,m33);
    mat3 matrix = mat3(col1, col2, col3);

    CameraPos = matrix * CameraPos;   // comment out for testing


}

// Rotate camera in y and z
void Camera::DoRotate(QPoint desc, QPoint orig)
{
    float YRot = (desc.x() - orig.x()) * RadPerPixel;
    float ZRot = (desc.y() - orig.y()) * RadPerPixel;

    RotateY(YRot);
    RotateZ(ZRot);

    // update xangle and yangle NOT WORKING YET!
    rotx(floor(YRot));
    roty(floor(ZRot));
}

// Update x coordinate of camera position
void Camera::setxFrom(int a)
{
    CameraPos.x=a;
}

// Update y coordinate of camera position
void Camera::setyFrom(int a)
{
    CameraPos.y=a;
}

// Update z coordinate of camera position
void Camera::setzFrom(int a)
{
    CameraPos.z=a;
}

// dolley in and out
void Camera::DoScale(QPoint desc, QPoint orig)
{
    float length = sqrt(CameraPos.x * CameraPos.x + CameraPos.y * CameraPos.y);
    float newLength = length + (desc.y() - orig.y()) * MovePerPixel;
    if (newLength > lim)
    {
        float ratio = newLength / length;
        /*CameraPos.x = CameraPos.x * ratio;
        CameraPos.y = CameraPos.y * ratio;
        CameraPos.z = CameraPos.z * ratio;*/

        scale = ratio;
    }


}

/* Individual rotations */
void Camera::rotx(int a)
{
        xangle =  (double)a;
}
void Camera::roty(int a)
{
        yangle =  (double)a;
}

void Camera::rotz(int a)
{
        zangle =  (double)a;
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
      camera_radius += (y - lastY) * 0.1f;
      if (camera_radius < 1) camera_radius = 1;
      if (camera_radius > 10) camera_radius = 10;
   }

   lastX = x;
   lastY = y;
}

void Camera::MouseButton(QMouseEvent *e, bool press)
{
    if (e->button() == Qt::LeftButton)
    {
        if (press == true) left_pressed = true;
        else left_pressed = false;
    };

    if (e->button() == Qt::RightButton)
    {
        if (press == true) right_pressed = true;
        else right_pressed = false;
    };
}

void Camera::updatePos()
{
    CameraPos.x = camera_radius * sin(camera_phi) * sin(camera_theta);
    CameraPos.y = camera_radius * cos(camera_phi);
    CameraPos.z = camera_radius * sin(camera_phi) * cos(camera_theta);
}

// maybe make a MouseRelease too??

//==================================================================
