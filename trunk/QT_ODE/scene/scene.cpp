#include "scene.h"

#include "graphics/glprimitive.h"
#include "graphics/material.h"
#include "graphics/camera.h"
#include "math/matrix4f.h"
#include "math/vector3f.h"
#include "scene/object.h"
#include "scene/character.h"
#include "scene/particle.h"
#include "scene/particleengine.h"
#include "graphics/glwidget.h"
#include "scene/joint.h"

//TODO remove QtOpenGL include, and everything else as necessary.

Scene::Scene(GLWidget *parent)
{
    this->parent = parent;

    Physics::initScene(this);
    camera = new Camera();

    camera->moveForward(-2000);
    camera->moveUp(200);

    Character *chara = new Character(this);
    this->characters.push_back(chara);

    addObject(OBJ_PLANE, MAT_GRAY_75, 0,
              Vector3f(50000, 0, 0),
              Vector3f(-25000, 0, -25000)
              );

    Object *leg1 = addObject(OBJ_BOX, MAT_YELLOW, chara,
                             Vector3f(50, 150, 50),
                             Vector3f(-50, 75, 0)
                             );

    Object *leg2 = addObject(OBJ_BOX, MAT_YELLOW, chara,
                             Vector3f(50, 150, 50),
                             Vector3f(50, 75, 0)
                             );

    Object *body = addObject(OBJ_BOX, MAT_YELLOW, chara,
                             Vector3f(50, 150, 50),
                             Vector3f(0, 225, 0)
                             );

    Object *arm1 = addObject(OBJ_BOX, MAT_YELLOW, chara,
                             Vector3f(50, 150, 50),
                             Vector3f(50, 225, 0)
                             );

    Joint *joint = new Joint(chara);
    joint->parent = body;
    joint->child = leg1;
    joint->init(-25,150,0);

    joint = new Joint(chara);
    joint->parent = body;
    joint->child = leg2;
    joint->init(25,150,0);

    joint = new Joint(chara);
    joint->parent = body;
    joint->child = arm1;
    joint->init(25,300,0);

    testObject = body;

    ParticleEngine *PE;
    particleEngines.push_back( PE = new PESignal(25,300,0,30,this) );
    PE->material->setDiffuse(MAT_WHITE);


    /*joint->parent = addObject(OBJ_BOX, MAT_MAGENTA, chara,
              Vector3f(200, 50, 300),
              Vector3f(200, 500, -1000)
              );

    testObject = joint->child = addObject(OBJ_BOX, MAT_YELLOW, chara,
              Vector3f(100, 100, 100),
              Vector3f(220, 1000, -910)
              );

    joint->init(200,750,-1000);
*/
/*
    addObject(OBJ_BOX, MAT_DARK_GREEN, chara,
                           Vector3f(100, 100, 100),
                           Vector3f(-200, 700, 100)
                           );

    addObject(OBJ_CYLINDER, MAT_ORANGE, 0,
              Vector3f(100, 100, 100),
              Vector3f(200, 1000, -300)
              );

    addObject(OBJ_SPHERE, MAT_BLUE, 0,
              Vector3f(100, 0, 0),
              Vector3f(-200, 200, -300)
              );

    addObject(OBJ_BOX, MAT_DARK_BLUE, 0,
              Vector3f(300, 100, 100),
              Vector3f(-210, 600, -290)
              );

    addObject(OBJ_CAPSULE, MAT_GRAY_50, 0,
              Vector3f(100, 100, 10),
              Vector3f(700, 200, -300)
              );

    addObject(OBJ_SPHERE, MAT_YELLOW, 0,
              Vector3f(100, 200, 10),
              Vector3f(-700, 200, -300)
              );

              //*/

    /*
    ParticleEngine *PE;
    particleEngines.push_back( PE = new PESignal(0,0,0,30,this) );
    PE->material->setDiffuse(MAT_WHITE);
    particleEngines.push_back( PE = new PESignal(100,-100,0,30,this) );
    PE->material->setDiffuse(MAT_GRAY_50);
    particleEngines.push_back( PE = new PESignal(-100,-100,0,30,this) );
    PE->material->setDiffuse(MAT_GRAY_25);
*/
}

Scene::~Scene(){
    Physics::closeScene(this);
    if(camera!=NULL){
        delete camera;
    }

    Camera *camera;
    std::vector<Object*> objects;
    std::vector<Character*> characters;
    //std::vector<Contact*> contacts;
    std::list<Particle*> particles;
    std::vector<ParticleEngine*> particleEngines;

    while(!objects.empty()){
        delete objects.back();
        objects.pop_back();
    }

    while(!particles.empty()){
        delete particles.back();
        particles.pop_back();
    }

    while(!particleEngines.empty()){
        delete particleEngines.back();
        particleEngines.pop_back();
    }

    while(!characters.empty()){
        delete characters.back();
        characters.pop_back();
    }
}

void Scene::draw()
{
    for(std::vector<ParticleEngine*>::iterator it = particleEngines.begin(); it!= particleEngines.end(); it++){
        (*it)->tick();
    }

    camera->glApply();

    for(std::vector<Character*>::iterator it = characters.begin(); it!= characters.end(); it++){
        (*it)->draw();
    }
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

Object* Scene::addObject(int shape, int diffuse, Character *character = 0, Vector3f properties = Vector3f(0,0,0), Vector3f position = Vector3f(0,0,0) )
{
    Object *obj = new Object(this);
    obj->shape = (OBJECT_SHAPE)shape;
    obj->material->setDiffuse(diffuse);
    *obj->initialPosition = position;
    obj->properties[0] = properties.getX();
    obj->properties[1] = properties.getY();
    obj->properties[2] = properties.getZ();
    obj->scene = this;

    if(shape == OBJ_PLANE){
        obj->transform->setIdentity();
        obj->transform->translate(position);
    }

    if(character == 0){
        objects.push_back(obj);
        Physics::createObject(obj, space, position);
    }else{
        character->objects.push_back(obj);
        Physics::createObject(obj, character->space, position);
    }

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
    for(int i=0;i<100;i++){
        if(testObject!=NULL){
            testObject->appForce(0,0,1000000);

            //testObject->appTorque(0,370000000,0);
            //        testObject->appTorque(0,37000000,0);
            //                testObject->appTorque(0,0,3700000000);
            //        testObject->appTorque(300000000,0,30000000);
        }
        Physics::simSingleStep(this);
    }
}
