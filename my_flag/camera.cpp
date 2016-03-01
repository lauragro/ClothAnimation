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

void Camera::startup()
{
    winw=this->width();  // width returns width of window
    winh=this->height();
    xangle= yangle= zangle=0.0;
    scale = 1.0;
    CameraPos.x = CameraPos.y = CameraPos.z = 0.0;
    Rotating = false;
    Scaling = false;
}

// Handle the mouse being pressed
void Camera::mousePressEvent(QMouseEvent *e)
{
    // Get mouse location
    QPoint MouseLocation = e->pos();

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
    }

    // Update the view
    //parent->updateGL();
}

// Handle the mouse being released
void Camera::mouseReleaseEvent(QMouseEvent *e)
{
    // Left button released when in rotate mode
    if (e->button() == Qt::LeftButton && Rotating)
    {
        DoRotate(e->pos(), lastMousePoint);
        Rotating = false;
    }

    // Right button released when in scale mode
    if (e->button() == Qt::RightButton && Scaling)
    {
        DoScale(e->pos(), lastMousePoint);
        Scaling = false;
    }

    // Update the view
    //updateGL();
}

// Handle the mouse being moved
void Camera::mouseMoveEvent(QMouseEvent *e)
{
    // Left button moved when in rotate mode
    if ((e->buttons() & Qt::LeftButton) && Rotating)
    {
        DoRotate(e->pos(), lastMousePoint);
        lastMousePoint = e->pos();
    }

    // Right button moved when in scale mode
    if ((e->buttons() & Qt::RightButton) && Scaling)
    {
        DoScale(e->pos(), lastMousePoint);
        lastMousePoint = e->pos();
    }

    // Update the view
    //updateGL();
}

// Rotate camera in y
void Camera::RotateY(glm::vec3 pVec, float rad)
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
    vec3 col1 = vec3(m11,m12,m13);
    vec3 col2 = vec3(m21,m22,m23);
    vec3 col3 = vec3(m31,m32,m33);
    mat3 matrix = mat3(col1, col2, col3);

    // perform rotation
    pVec = matrix * pVec;

}

// Rotate camera in z
void Camera::RotateZ(glm::vec3 pVec, float rad)
{
    // compute trig
    float cosPhi = (float)cos(rad);
    float sinPhi = (float)sin(rad);

    // define all values of matrix
    m11 = cosPhi;   //m11
    m12 = - sinPhi; //m12
    m13 = 0.0f;     //m13
    m21 = sinPhi;   //m21
    m22 = cosPhi;   //m22
    m23 = 0.0f;     //m23
    m31 = 0.0f;     //m31
    m32 = 0.0f;     //m32
    m33 = 1.0f;     //m33

    // put values in a matrix
    vec3 col1 = vec3(m11,m12,m13);
    vec3 col2 = vec3(m21,m22,m23);
    vec3 col3 = vec3(m31,m32,m33);
    mat3 matrix = mat3(col1, col2, col3);

    // perform rotation
    pVec = matrix * pVec;

}

// Rotate camera in y and z
void Camera::DoRotate(QPoint desc, QPoint orig)
{
    float YRot = (desc.x() - orig.x()) * RadPerPixel;
    float ZRot = (desc.y() - orig.y()) * RadPerPixel;

    RotateY(CameraPos, YRot);
    RotateZ(CameraPos, ZRot);
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

// Zoom in and out
void Camera::DoScale(QPoint desc, QPoint orig)
{
    float length = sqrt(CameraPos.x * CameraPos.x + CameraPos.y * CameraPos.y);
    float newLength = length + (desc.y() - orig.y()) * MovePerPixel;
    if (newLength > lim)
    {
        float ratio = newLength / length;
        CameraPos.x = CameraPos.x * ratio;
        CameraPos.y = CameraPos.y * ratio;
        CameraPos.z = CameraPos.z * ratio;
    }
}
