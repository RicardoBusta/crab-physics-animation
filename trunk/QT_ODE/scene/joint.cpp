#include "joint.h"

#include "physics/physics.h"
#include "math/vector3f.h"
#include "scene/character.h"
#include "graphics/glprimitive.h"
#include "graphics/material.h"
#include "math/matrix4f.h"
#include "graphics/glutil.h"

#include <QtOpenGL>

Joint::Joint(Character *chara)
{
    this->character = chara;
    chara->joints.push_back(this);

    material = new Material();
    material->setDiffuse(MAT_RED);
    transform = new Matrix4f();
    transform->setIdentity();
}

Joint::~Joint(){
    Physics::closeJoint(this);

    if(material!=0){
        delete material;
    }
    if(transform!=0){
        delete transform;
    }
}

void Joint::init(Vector3f anchor)
{
    Physics::initJointBall(this, anchor);
}

void Joint::setColor(int color)
{
    material->setDiffuse(color);
}

void Joint::draw()
{
    Vector3f pos = Physics::getJointBallAnchor( this );

    transform->setPos( pos );

    GLPrimitive::sphere( 0.5, material, transform );

    glDisable(GL_DEPTH_TEST);
    glPushMatrix();
    glTranslatef(pos.getX(), pos.getY(), pos.getZ());
    GLUtil::glSphereBillBoard();
    GLPrimitive::bb_circle( 1.0, material );
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
}
