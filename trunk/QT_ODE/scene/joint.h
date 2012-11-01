#ifndef JOINT_H
#define JOINT_H

#include "physics/physics.h"

class Object;
class Character;

class Joint
{
public:

    JointID joint;
    Object *parent;
    Object *child;

    Character *character;

    Joint(Character *chara);
    ~Joint();

    void init(Vector3f anchor);

    void draw();
};

#endif // JOINT_H
