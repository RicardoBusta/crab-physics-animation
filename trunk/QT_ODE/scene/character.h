#ifndef CHARACTER_H
#define CHARACTER_H

#include "physics/physics.h"

#include <vector>

class Object;
class Joint;
class Scene;

class Character
{
public:
    Character(Scene *scene);
    ~Character();

    Scene *scene;

    SpaceID space;
    JointGroupID jointGroup;

    std::vector<Object*> objects;
    std::vector<Joint*> joints;

    void draw();
};

#endif // CHARACTER_H
