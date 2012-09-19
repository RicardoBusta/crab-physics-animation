#ifndef OBJECT_H
#define OBJECT_H

class Matrix4f;
class Material;

#include "physics/physics.h"

enum OBJECT_SHAPE{OBJ_PLANE, OBJ_BOX, OBJ_CAP, OBJ_CYL, OBJ_SPHERE};

class Object
{
public:
    Object();
    ~Object();

    void draw();
public:

    //------------------
    // Physics

    BodyID body;
    GeomID geometry;

    //------------------
    // Graphics

    OBJECT_SHAPE shape;
    float properties[3];

    Matrix4f *transform;

    // Properties
    // box      0:x 1:y 2:z
    // capsule  0:r 1:l
    // cylinder 0:r 1:l
    // sphere   0:r
    Material *material;
};

#endif // OBJECT_H
