#ifndef OBJECT_H
#define OBJECT_H

class Matrix4f;
class Material;

#include "physics/physics.h"

class Scene;

enum OBJECT_SHAPE{OBJ_PLANE, OBJ_BOX, OBJ_CAPSULE, OBJ_CYLINDER, OBJ_SPHERE};

class Object
{
public:
    Object(Scene *scene);
    ~Object();

    void draw();
public:
    Scene *scene;

    //------------------
    // Physics

    BodyID body;
    GeomID geometry;
    Mass mass;

    void appTorque(float x, float y, float z);
    void appForce(float x, float y, float z);

    //------------------
    // Graphics

    OBJECT_SHAPE shape;
    float properties[3];
    float initialPosition[3];

    Matrix4f *transform;

    // Properties
    // box      0:x 1:y 2:z
    // capsule  0:r 1:l
    // cylinder 0:r 1:l
    // sphere   0:r
    Material *material;
};

#endif // OBJECT_H
