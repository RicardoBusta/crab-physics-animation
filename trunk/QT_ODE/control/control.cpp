#include "control.h"

#include "scene/scene.h"
#include "graphics/camera.h"

Control::Control(Scene *scene){
    this->scene = scene;
}

void Control::rotateCamera(float rx, float ry){
    if(scene != 0){
        scene->camera->rotateSide(rx);
        scene->camera->rotateUp(-ry);
    }
}

void Control::moveCamera(float mx, float my){
    if(scene != 0){
        scene->camera->moveSide(-mx);
        scene->camera->moveUp(my);
    }
}
