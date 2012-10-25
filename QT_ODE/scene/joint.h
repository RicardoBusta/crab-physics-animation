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

    void init(int x, int y, int z);

    ~Joint();
};

#endif // JOINT_H
