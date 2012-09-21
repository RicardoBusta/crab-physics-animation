#include "scene.h"

#include <QtOpenGL>

#include "physics/physics.h"
#include "graphics/glprimitive.h"
#include "graphics/material.h"
#include "graphics/camera.h"
#include "math/matrix4f.h"
#include "scene/object.h"

//TODO remove QtOpenGL include, and everything else as necessary.

Scene::Scene()
{
    Physics::init();
    camera = new Camera();

    camera->moveForward(-2000);
    camera->moveUp(200);

    Object *obj;

    obj = new Object();
    obj->shape = OBJ_PLANE;
    obj->material->setDiffuse(MAT_GRAY_75);
    obj->material->setSpecular(MAT_WHITE);
    obj->transform->translate(-2500,-100,-2500);
    obj->properties[0] = 5000;
    objList.push_back(obj);

    obj = new Object();
    obj->shape = OBJ_SPHERE;
    obj->material->setDiffuse(MAT_MAGENTA);
    obj->material->setSpecular(MAT_WHITE);
    obj->transform->translate(200,0,100);
    obj->properties[0] = 100;
    objList.push_back(obj);

    obj = new Object();
    obj->shape = OBJ_BOX;
    obj->material->setDiffuse(MAT_DARK_GREEN);
    obj->material->setSpecular(MAT_WHITE);
    obj->transform->translate(-200,0,100);
    obj->properties[0] = 100;
    obj->properties[1] = 100;
    obj->properties[2] = 100;
    objList.push_back(obj);

    obj = new Object();
    obj->shape = OBJ_BOX;
    obj->material->setDiffuse(MAT_ORANGE);
    obj->material->setSpecular(MAT_WHITE);
    obj->transform->translate(200,0,-300);
    obj->properties[0] = 100;
    obj->properties[1] = 100;
    obj->properties[2] = 100;
    objList.push_back(obj);

    obj = new Object();
    obj->shape = OBJ_SPHERE;
    obj->material->setDiffuse(MAT_BLUE);
    obj->material->setSpecular(MAT_WHITE);
    obj->transform->translate(-200,0,-300);
    obj->properties[0] = 100;
    objList.push_back(obj);

    obj = new Object();
    obj->shape = OBJ_CYLINDER;
    obj->material->setDiffuse(MAT_YELLOW);
    obj->material->setSpecular(MAT_WHITE);
    obj->transform->translate(-500,0,-300);
    obj->properties[0] = 100;
    obj->properties[1] = 200;
    objList.push_back(obj);

    obj = new Object();
    obj->shape = OBJ_CYLINDER;
    obj->material->setDiffuse(MAT_WHITE);
    obj->material->setSpecular(MAT_WHITE);
    obj->transform->translate(-500,0,100);
    obj->properties[0] = 100;
    obj->properties[1] = 200;
    objList.push_back(obj);

    obj = new Object();
    obj->shape = OBJ_CAPSULE;
    obj->material->setDiffuse(MAT_BLACK);
    obj->material->setSpecular(MAT_WHITE);
    obj->transform->translate(-700,0,100);
    obj->properties[0] = 100;
    obj->properties[1] = 200;
    objList.push_back(obj);

    obj = new Object();
    obj->shape = OBJ_CAPSULE;
    obj->material->setDiffuse(MAT_BLACK);
    obj->material->setSpecular(MAT_WHITE);
    obj->transform->translate(-700,0,100);
    obj->properties[0] = 100;
    obj->properties[1] = 200;
    objList.push_back(obj);
}

Scene::~Scene(){
    Physics::close();
    if(camera!=NULL){
        delete camera;
    }

    while(!objList.empty()){
        delete objList.back();
        objList.pop_back();
    }
}

void Scene::draw()
{
    camera->glApply();

    for(std::vector<Object*>::iterator it = objList.begin(); it!= objList.end(); it++){
        (*it)->draw();
    }

}

void Scene::simulation()
{
}


