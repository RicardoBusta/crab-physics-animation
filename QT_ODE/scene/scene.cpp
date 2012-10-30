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
#include "scene/prop.h"

//TODO remove QtOpenGL include, and everything else as necessary.

Scene::Scene(GLWidget *parent)
{
    this->parent = parent;

    Physics::initScene(this);
    camera = new Camera();

    floor = new Prop(this,PROP_PLANE);

    camera->moveForward(-200.0);
    camera->moveUp(20.0);

    Character *chara = new Character(this);
    this->characters.push_back(chara);

    Object *leg_right = addObject(OBJ_BOX, MAT_CYAN, chara,
                                  Vector3f(5.0, 15.0, 5.0),
                                  Vector3f(-2.5, 7.5, 0)
                                  );

    Object *leg_left = addObject(OBJ_BOX, MAT_YELLOW, chara,
                                 Vector3f(5.0, 15.0, 5.0),
                                 Vector3f(2.5, 7.5, 0)
                                 );

    Object *body = addObject(OBJ_BOX, MAT_WHITE, chara,
                             Vector3f(5.0, 15.0, 5.0),
                             Vector3f(0, 22.5, 0)
                             );

    Object *arm_left = addObject(OBJ_BOX, MAT_YELLOW, chara,
                                 Vector3f(5.0, 15.0, 5.0),
                                 Vector3f(5.0, 22.5, 0)
                                 );

    Object *arm_right = addObject(OBJ_BOX, MAT_CYAN, chara,
                                  Vector3f(5.0, 15.0, 5.0),
                                  Vector3f(-5.0, 22.5, 0)
                                  );

    Object *head = addObject(OBJ_BOX, MAT_ORANGE, chara,
                             Vector3f(7.0, 7.0, 7.0),
                             Vector3f(0, 33.5, 0)
                             );

    addJointBall(Vector3f(-2.5,15.0,0), body, leg_right, chara);

    addJointBall(Vector3f(2.5,15.0,0), body, leg_left, chara);

    addJointBall(Vector3f(-2.5,30.0,0), body, arm_right, chara);

    addJointBall(Vector3f(2.5,30.0,0), body, arm_left, chara);

    addJointBall(Vector3f(0,30.0,0), body, head, chara);

    testObject = head;

  /*  ParticleEngine *PE;
    particleEngines.push_back( PE = new PESignal(2.5,30.0,0,15,this) );
    PE->material->setDiffuse(MAT_BLACK);*/
}

Scene::~Scene(){
    Physics::closeScene(this);

    if(camera!=NULL){
        delete camera;
    }

    std::vector<Character*> characters;
    //std::vector<Contact*> contacts;

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

    floor->draw();

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

    if(character == 0){
        objects.push_back(obj);
        Physics::createObject(obj, space, position);
    }else{
        character->objects.push_back(obj);
        Physics::createObject(obj, character->space, position);
    }

    return obj;
}

Joint *Scene::addJointBall(Vector3f anchor, Object *parent, Object *child, Character *chara){
    Joint *joint = NULL;
    if(chara != NULL){
        joint = new Joint(chara);
        joint->parent = parent;
        joint->child = child;
        joint->init(anchor);
    }
    return joint;
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
    for(int i=0;i<10;i++){
        if(testObject!=NULL){
            testObject->appForce(0,0,10000);

            //testObject->appTorque(0,370000000,0);
            //        testObject->appTorque(0,37000000,0);
            //                testObject->appTorque(0,0,3700000000);
            //        testObject->appTorque(300000000,0,30000000);
        }
        Physics::simSingleStep(this);
    }
}
