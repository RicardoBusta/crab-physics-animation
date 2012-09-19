#ifndef OBJECT_H
#define OBJECT_H

#include "physics/physics.h"
#include "graphics/material.h"

enum OBJECT_SHAPE{OBJ_BOX, OBJ_CAP, OBJ__CYL, OBJ_SPH};

class Object
{
public:
    Object();

    void draw();
private:

    //------------------
    // Physics

    BodyID body;
    GeomID geometry;

    //------------------
    // Graphics

    int shape;
    float properties[3];
    // Properties
    // box      0:x 1:y 2:z
    // capsule  0:r 1:l
    // cylinder 0:r 1:l
    // sphere   0:r
    Material material;
};

#endif // OBJECT_H
