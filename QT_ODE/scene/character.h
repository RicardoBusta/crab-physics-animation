#ifndef CHARACTER_H
#define CHARACTER_H

#include "physics/physics.h"

#include <vector>

class Object;
class Joint;

class Character
{
public:
    Character();

    SpaceID space;
    JointGroupID jointGroup;

    std::vector<Object*> objects;
    std::vector<Joint*> joints;

    void draw();
};

#endif // CHARACTER_H
