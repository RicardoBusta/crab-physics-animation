#include "character.h"

#include "scene/object.h"

Character::Character()
{
}

void Character::draw()
{
    for(std::vector<Object*>::iterator it=objects.begin(); it!=objects.end(); it++){
        (*it)->draw();
    }
}
