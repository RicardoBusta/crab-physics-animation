#include "character.h"

#include "scene/object.h"
#include "physics/physics.h"
#include "scene/joint.h"

Character::Character(Scene *parent)
{
    this->scene = parent;
    Physics::initCharacter(this);
}

Character::~Character(){
    Physics::closeCharacter(this);

    while(!objects.empty()){
        delete objects.back();
        objects.pop_back();
    }

    while(!joints.empty()){
        delete joints.back();
        joints.pop_back();
    }
}

//#include <QtOpenGL>

void Character::draw()
{
    for(std::vector<Object*>::iterator it=objects.begin(); it!=objects.end(); it++){
        (*it)->draw();
    }
//    glDisable(GL_DEPTH_TEST);
    for(std::vector<Joint*>::iterator it=joints.begin(); it!=joints.end(); it++){
        (*it)->draw();
    }
//    glEnable(GL_DEPTH_TEST);
}
