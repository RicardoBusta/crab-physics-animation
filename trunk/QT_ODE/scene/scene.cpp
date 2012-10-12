#include "scene.h"

#include "graphics/glprimitive.h"
#include "graphics/material.h"
#include "graphics/camera.h"
#include "math/matrix4f.h"
#include "math/vector3f.h"
#include "scene/object.h"
#include "scene/particle.h"
#include "scene/particleengine.h"

//TODO remove QtOpenGL include, and everything else as necessary.

Scene::Scene()
{
    Physics::init(this);
    camera = new Camera();

    camera->moveForward(-2000);
    camera->moveUp(200);

    addObject(OBJ_PLANE, MAT_GRAY_75, MAT_WHITE,
              5000, 0, 0,
              Vector3f(-2500, 0, -2500)
              );

    addObject(OBJ_SPHERE, MAT_MAGENTA, MAT_WHITE,
              200, 0, 0,
              Vector3f(200, 500, -1000)
              );

    testObject = addObject(OBJ_BOX, MAT_DARK_GREEN, MAT_WHITE,
                           100, 100, 100,
                           Vector3f(-200, 700, 100)
                           );

    addObject(OBJ_BOX, MAT_ORANGE, MAT_WHITE,
              100, 100, 100,
              Vector3f(200, 1000, -300)
              );

    addObject(OBJ_SPHERE, MAT_BLUE, MAT_WHITE,
              100, 0, 0,
              Vector3f(-200, 200, -300)
              );

    addObject(OBJ_CAPSULE, MAT_GRAY_25, MAT_WHITE,
              100, 100, 0,
              Vector3f(700, 200, -300)
              );

    addObject(OBJ_CYLINDER, MAT_YELLOW, MAT_WHITE,
              100, 200, 0,
              Vector3f(-700, 200, -300)
              );

    ParticleEngine *PE;
    particleEngines.push_back( PE = new PESignal(0,0,0,60,this) );
    PE->material->setDiffuse(MAT_RED);
    particleEngines.push_back( PE = new PESignal(500,0,0,30,this) );
    PE->material->setDiffuse(MAT_GREEN);
    particleEngines.push_back( PE = new PESignal(-500,0,0,10,this) );
    PE->material->setDiffuse(MAT_BLUE);
}

Scene::~Scene(){
    Physics::close(this);
    if(camera!=NULL){
        delete camera;
    }

    while(!objects.empty()){
        delete objects.back();
        objects.pop_back();
    }
}

void Scene::draw()
{
    for(std::vector<ParticleEngine*>::iterator it = particleEngines.begin(); it!= particleEngines.end(); it++){
        (*it)->tick();
    }

    camera->glApply();

    for(std::vector<Object*>::iterator it = objects.begin(); it!= objects.end(); it++){
        (*it)->draw();
    }

    for(std::list<Particle*>::iterator it = particles.begin(); it!= particles.end(); it++){
        if((*it)->alive){
            (*it)->behave();
        }else{
            Particle *p = (*it);
            it--;
            particles.remove(p);
            delete p;
        }
    }
}

Object* Scene::addObject(int shape, int diffuse, int specular, float prop0, float prop1=0, float prop2=0, Vector3f position = Vector3f(0,0,0) )
{
    Object *obj = new Object(this);
    obj->shape = (OBJECT_SHAPE)shape;
    obj->material->setDiffuse(diffuse);
    obj->material->setSpecular(specular);
    *obj->initialPosition = position;
    obj->properties[0] = prop0;
    obj->properties[1] = prop1;
    obj->properties[2] = prop2;
    objects.push_back(obj);

    if(shape == OBJ_PLANE){
        obj->transform->setIdentity();
        obj->transform->translate(position);
    }

    obj->scene = this;

    Physics::createObject(obj, position);

    return obj;
}

void Scene::addParticle(Particle *particle)
{
    if(particle!=NULL){
        particles.push_back( particle );
    }
}

//Physics

void Scene::simulationStep()
{
    for(int i=0;i<1000;i++){
        //testObject->appForce(0,61700000,0);
        //                testObject->appTorque(3700000000,0,0);
        //        testObject->appTorque(0,37000000,0);
        //                testObject->appTorque(0,0,3700000000);
//        testObject->appTorque(300000000,0,30000000);
        Physics::simSingleStep(this);
    }
}
