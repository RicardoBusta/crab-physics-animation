#include "control.h"

#include "scene/scene.h"
#include "graphics/camera.h"

#include "math/vector3f.h"

Control::Control(Scene *scene){
    this->scene = scene;
}

void Control::rotateCamera(float rx, float ry){
    if(scene != 0){
        scene->camera->rotateSide(rx*0.01);
        scene->camera->rotateUp(-ry*0.01);
    }
}

void Control::moveCamera(float mx, float my){
    if(scene != 0){
        scene->camera->moveSide(-mx*0.01);
        scene->camera->moveUp(my*0.01);
    }
}

void Control::applyForce(float x, float y)
{
    *scene->externalForce = scene->camera->side->realProduct(x*0.5).add( scene->camera->up->realProduct(y*0.5) );
}

void Control::applyTorque(float x, float y)
{
    *scene->externalTorque = scene->camera->side->realProduct(x*0.5).add( scene->camera->up->realProduct(y*0.5) );
}
