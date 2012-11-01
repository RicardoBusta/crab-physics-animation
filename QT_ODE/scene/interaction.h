#ifndef INTERACTION_H
#define INTERACTION_H

#include "math/vector3f.h"

class Interaction
{
public:
    Interaction();

    Vector3f force;
    Vector3f torque;
};

#endif // INTERACTION_H
