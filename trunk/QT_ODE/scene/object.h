#ifndef OBJECT_H
#define OBJECT_H

class Matrix4f;
class Material;
class Scene;
class Vector3f;

#include "physics/physics.h"

enum OBJECT_SHAPE{OBJ_BOX, OBJ_CAPSULE, OBJ_CYLINDER, OBJ_SPHERE};

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
    void appTorque(Vector3f *torque);
    void appForce(float x, float y, float z);
    void appForce(Vector3f *force);

    //------------------
    // Graphics

    OBJECT_SHAPE shape;
    float properties[3];
    Vector3f *initialPosition;
    Matrix4f *transform;

    // Properties
    // box      0:x 1:y 2:z
    // capsule  0:r 1:l
    // cylinder 0:r 1:l
    // sphere   0:r
    Material *material;
};

#endif // OBJECT_H
