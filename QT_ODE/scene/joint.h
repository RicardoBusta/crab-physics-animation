#ifndef JOINT_H
#define JOINT_H

#include "physics/physics.h"

class Object;
class Character;
class Material;

class Joint
{
public:

    JointID joint;
    Object *parent;
    Object *child;
    Material *material;
    Matrix4f *transform;

    Vector3f *initialAnchor;

    Character *character;

    Joint(Character *chara);
    ~Joint();

    void init(Vector3f anchor);
    void setColor(int color);

    void draw();
};

#endif // JOINT_H
