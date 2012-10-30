#include "joint.h"

#include "physics/physics.h"
#include "math/vector3f.h"
#include "scene/character.h"

Joint::Joint(Character *chara)
{
    this->character = chara;
    chara->joints.push_back(this);
}

Joint::~Joint(){
    Physics::closeJoint(this);
}

void Joint::init(Vector3f anchor)
{
    Physics::initJointBall(this, anchor);
}
