#include "scene.h"

#include <QtOpenGL>

#include "graphics/glprimitive.h"
#include "graphics/material.h"
#include "graphics/camera.h"
#include "math/matrix4f.h"
#include "scene/object.h"

//TODO remove QtOpenGL include, and everything else as necessary.

Scene::Scene()
{
    Physics::init(this);
    camera = new Camera();

    camera->moveForward(-2000);
    camera->moveUp(200);

    addObject(OBJ_PLANE, MAT_GRAY_75, MAT_WHITE,
              5000, 0, 0,
              -2500, 0, -2500);

    addObject(OBJ_SPHERE, MAT_MAGENTA, MAT_WHITE,
              200, 0, 0,
              200, 500, 100);

    addObject(OBJ_BOX, MAT_DARK_GREEN, MAT_WHITE,
              100, 100, 100,
              -200, 700, 100);

    addObject(OBJ_BOX, MAT_ORANGE, MAT_WHITE,
              100, 100, 100,
              200, 1000, -300);

    addObject(OBJ_SPHERE, MAT_BLUE, MAT_WHITE,
              100, 0, 0,
              -200, 200, -300);

    addObject(OBJ_CAPSULE, MAT_GRAY_25, MAT_WHITE,
              100, 100, 0,
              700, 200, -300);

    testObject = addObject(OBJ_CYLINDER, MAT_YELLOW, MAT_WHITE,
              100, 100, 0,
              -700, 200, -300);
}

Scene::~Scene(){
    Physics::close(this);
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

Object* Scene::addObject(int shape, int diffuse, int specular, float prop0, float prop1=0, float prop2=0, float posx=0, float posy=0, float posz=0 )
{
    Object *obj = new Object(this);
    obj->shape = (OBJECT_SHAPE)shape;
    obj->material->setDiffuse(diffuse);
    obj->material->setSpecular(specular);
    obj->initialPosition[0] = posx;
    obj->initialPosition[1] = posy;
    obj->initialPosition[2] = posz;
    obj->properties[0] = prop0;
    obj->properties[1] = prop1;
    obj->properties[2] = prop2;
    objList.push_back(obj);

    if(shape == OBJ_PLANE){
        obj->transform->setIdentity();
        obj->transform->translate(posx,posy,posz);
    }

    obj->scene = this;

    Physics::createObject(obj, posx, posy, posz);

    return obj;
}

//Physics

void Scene::simulationStep()
{
    for(int i=0;i<1000;i++){
        //testObject->appForce(200000,0,0);
        testObject->appTorque(500000000,0,0);
        Physics::simSingleStep(this);
    }
}
