#include "vector3d.h"
#include <math.h>

// constructor/destructor
Vector3D::Vector3D()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Vector3D::Vector3D(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::~Vector3D()
{
    delete this;
}


/* operators */

// ADD
Vector3D* Vector3D::add(Vector3D a, Vector3D b)
{
    return new Vector3D(a.x+b.x, a.y+b.y, a.z+b.z);
}

// SUBTRACT
Vector3D* Vector3D::subtract(Vector3D a, Vector3D b)
{
    return new Vector3D(a.x-b.x, a.y-b.y, a.z-b.z);
}

// SCALE UP
Vector3D* Vector3D::scaleUp(Vector3D a, double factor)
{
    return new Vector3D(factor*a.x, factor*a.y, factor*a.z);
}

// SCALE DOWN
Vector3D* Vector3D::scaleDown(Vector3D a, double factor)
{
    return new Vector3D(a.x/factor, a.y/factor, a.z/factor);
}

// DOT PRODUCT
double Vector3D::dot(Vector3D a, Vector3D b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

// CROSS PRODUCT
Vector3D* Vector3D::cross(Vector3D a, Vector3D b)
{
    double i,j,k;

    i = a.y*b.z - a.z*b.y;
    j = -(a.x*b.z - a.z*b.x);
    k = a.x*b.y - a.y*b.x;

    return new Vector3D(i,j,k);
}

// MAGNITUDE
double Vector3D::magnitude(Vector3D a)
{
    return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

// NORMALIZE
Vector3D* Vector3D::normalize(Vector3D a)
{
    double mag;
    mag = magnitude(a);
    return scaleDown(a,mag);
}
