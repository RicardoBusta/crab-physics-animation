#include "character.h"

#include "scene/object.h"
#include "physics/physics.h"

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

void Character::draw()
{
    for(std::vector<Object*>::iterator it=objects.begin(); it!=objects.end(); it++){
        (*it)->draw();
    }
}
