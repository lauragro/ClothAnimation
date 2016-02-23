#ifndef VECTOR3D_H
#define VECTOR3D_H


class Vector3D
{
public:
    // constructor/destructor
    Vector3D();
    Vector3D(double x, double y, double z);
    ~Vector3D();

    // components
    double x,y,z;

    // operators
    Vector3D* add(Vector3D *a, Vector3D *b);
    Vector3D* subtract(Vector3D *a, Vector3D *b);
    Vector3D* scaleUp(Vector3D *a, double factor);
    Vector3D* scaleDown(Vector3D *a, double factor);
    double dot(Vector3D *a, Vector3D *b);
    Vector3D* cross(Vector3D *a, Vector3D *b);
    double magnitude(Vector3D *a);
    Vector3D* normalize(Vector3D *a);

};

#endif // VECTOR3D_H
