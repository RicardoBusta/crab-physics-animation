#include "character.h"

#include "scene/object.h"
#include "physics/physics.h"

Character::Character(Scene *parent)
{
    this->parent = parent;
    Physics::initCharacter(this);
}

Character::~Character(){
    while(!objects.empty()){
        delete objects.back();
        objects.pop_back();
    }

    while(!joints.empty()){
        delete joints.back();
        joints.pop_back();
    }

    Physics::closeCharacter(this);
}

void Character::draw()
{
    for(std::vector<Object*>::iterator it=objects.begin(); it!=objects.end(); it++){
        (*it)->draw();
    }
}
