#include "joint.h"

#include "physics/physics.h"
#include "math/vector3f.h"
#include "scene/character.h"
#include "graphics/glprimitive.h"
#include "graphics/material.h"
#include "math/matrix4f.h"

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

void Joint::draw()
{
    Vector3f pos = Physics::getJointBallAnchor( this );

    Material mat;
    mat.setDiffuse(MAT_RED);
    Matrix4f tra;
    tra.setIdentity();
    tra.translate( pos );

    GLPrimitive::sphere( 1, &mat, &tra );
}
