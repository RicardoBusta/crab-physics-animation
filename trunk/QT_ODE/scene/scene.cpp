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

//TODO remove parameters from scene.
double omega = -90;
dQuaternion tarQ = {
    cos(omega*(M_PI_2/180)),
    sin(omega*(M_PI_2/180)),
    0,
    0
};

double ks = 2000000;
double kd = 2000000;

Scene::Scene(GLWidget *parent)
{
    this->parent = parent;

    externalForce = new Vector3f(0,0,0);
    externalTorque = new Vector3f(0,0,0);

    Physics::initScene(this);
    camera = new Camera();

    floor = new Prop(this,PROP_PLANE);

    camera->moveForward(-200.0);
    camera->moveUp(20.0);

    Character *chara = new Character(this);
    this->characters.push_back(chara);

    Vector3f footDimension(5,5,10);
    Vector3f legDimension(4,8,4);
    Vector3f armDimension(4,8,4);
    Vector3f bodyDimension(10,16,5);
    Vector3f headDimension(6,8,6);
    Vector3f handDimension(5,5,5);


    Object *botpiece = addObject(OBJ_BOX, MAT_ORANGE, chara,
                                   Vector3f(5,5,30),
                                   Vector3f(0,40,15)
                                   );
    Object *toppiece = addObject(OBJ_BOX, MAT_YELLOW, chara,
                                   Vector3f(5,5,30),
                                   Vector3f(0,40,-15)
                                   );
    selectedObjects.push_back(toppiece);

    interestJoint = addJointBall(Vector3f(0,40,0), toppiece, botpiece, chara);
    //*/


/*
    Object *foot_right = addObject(OBJ_BOX, MAT_DARK_ORANGE, chara,
                                   footDimension,
                                   Vector3f(-footDimension.getX()/2, footDimension.getY()/2, (footDimension.getZ()-legDimension.getZ())/2)
                                   );
    Object *leg1_right = addObject(OBJ_BOX, MAT_ORANGE, chara,
                                   legDimension,
                                   Vector3f(-bodyDimension.getX()/4, (legDimension.getY()/2) + footDimension.getY(), 0)
                                   );
    Object *leg2_right = addObject(OBJ_BOX, MAT_ORANGE, chara,
                                   legDimension,
                                   Vector3f(-bodyDimension.getX()/4, (legDimension.getY()/2) + legDimension.getY() + footDimension.getY(), 0)
                                   );

    Object *foot_left = addObject(OBJ_BOX, MAT_DARK_YELLOW, chara,
                                  footDimension,
                                  Vector3f(footDimension.getX()/2, footDimension.getY()/2, (footDimension.getZ()-legDimension.getZ())/2)
                                  );
    Object *leg1_left = addObject(OBJ_BOX, MAT_YELLOW, chara,
                                  legDimension,
                                  Vector3f(bodyDimension.getX()/4, (legDimension.getY()/2) + footDimension.getY(), 0)
                                  );
    Object *leg2_left = addObject(OBJ_BOX, MAT_YELLOW, chara,
                                  legDimension,
                                  Vector3f(bodyDimension.getX()/4, (legDimension.getY()/2) + legDimension.getY() + footDimension.getY(), 0)
                                  );


    Object *body_bot = addObject(OBJ_BOX, MAT_WHITE, chara,
                                 bodyDimension.addY(-bodyDimension.getY()/2),
                                 Vector3f(0, (bodyDimension.getY()/4) + footDimension.getY() + (2*legDimension.getY()), 0)
                                 );

    Object *body_top = addObject(OBJ_BOX, MAT_WHITE, chara,
                                 bodyDimension.addY(-bodyDimension.getY()/2),
                                 Vector3f(0, (bodyDimension.getY()*3/4) + footDimension.getY() + (2*legDimension.getY()), 0)
                                 );

    Object *arm2_left = addObject(OBJ_BOX, MAT_YELLOW, chara,
                                  armDimension,
                                  Vector3f((bodyDimension.getX()+armDimension.getX())/2, bodyDimension.getY() + footDimension.getY() + (2*legDimension.getY()) - armDimension.getY()/2, 0)
                                  );
    Object *arm1_left = addObject(OBJ_BOX, MAT_YELLOW, chara,
                                  armDimension,
                                  Vector3f((bodyDimension.getX()+armDimension.getX())/2, bodyDimension.getY() + footDimension.getY() + (2*legDimension.getY()) - armDimension.getY()*3/2, 0)
                                  );
    Object *arm2_right = addObject(OBJ_BOX, MAT_ORANGE, chara,
                                   armDimension,
                                   Vector3f(-(bodyDimension.getX()+armDimension.getX())/2, bodyDimension.getY() + footDimension.getY() + (2*legDimension.getY()) - armDimension.getY()/2, 0)
                                   );
    Object *arm1_right = addObject(OBJ_BOX, MAT_ORANGE, chara,
                                   armDimension,
                                   Vector3f(-(bodyDimension.getX()+armDimension.getX())/2, bodyDimension.getY() + footDimension.getY() + (2*legDimension.getY()) - armDimension.getY()*3/2, 0)
                                   );

    Object *hand_left = addObject(OBJ_BOX, MAT_DARK_YELLOW, chara,
                                  handDimension,
                                  Vector3f((bodyDimension.getX()+armDimension.getX())/2, bodyDimension.getY() + footDimension.getY() + (2*legDimension.getY()) - (armDimension.getY()*2) - handDimension.getY()/2 , 0)
                                  );

    Object *hand_right = addObject(OBJ_BOX, MAT_DARK_ORANGE, chara,
                                   handDimension,
                                   Vector3f(-(bodyDimension.getX()+armDimension.getX())/2, bodyDimension.getY() + footDimension.getY() + (2*legDimension.getY()) - (armDimension.getY()*2) - handDimension.getY()/2 , 0)
                                   );



    Object *head = addObject(OBJ_BOX, MAT_DARK_BLUE, chara,
                             headDimension,
                             Vector3f(0, footDimension.getY()+2*legDimension.getY()+bodyDimension.getY()+(headDimension.getY()/2), 0)
                             );

    selectedObjects.push_back(head);
    //selectedObjects.push_back(hand_left);
    //    selectedObjects.push_back(hand_right);
    //    selectedObjects.push_back(foot_right);
    //    selectedObjects.push_back(foot_left);

    Joint *joint;

    joint = addJointBall(leg2_left->initialPosition->addY( legDimension.getY()/2 ), body_bot, leg2_left, chara);
    joint->setColor(MAT_GREEN);
    joint = addJointBall(leg1_left->initialPosition->addY( legDimension.getY()/2 ), leg2_left, leg1_left, chara);
    joint->setColor(MAT_GREEN);
    joint = addJointBall(foot_left->initialPosition->addY( footDimension.getY()/2 ).addZ((legDimension.getZ()-footDimension.getZ())/2), leg1_left, foot_left, chara);
    joint->setColor(MAT_GREEN);

    joint = addJointBall(arm2_left->initialPosition->addY( armDimension.getY()/2 ).addX( -armDimension.getX()/2 ), body_top, arm2_left, chara);
    joint->setColor(MAT_GREEN);
    joint = addJointBall(arm1_left->initialPosition->addY( armDimension.getY()/2 ), arm2_left, arm1_left, chara);
    joint->setColor(MAT_GREEN);
    interestJoint = joint;
    joint = addJointBall(hand_left->initialPosition->addY( handDimension.getY()/2 ), arm1_left, hand_left, chara);
    joint->setColor(MAT_GREEN);


    joint = addJointBall(leg2_right->initialPosition->addY( legDimension.getY()/2 ), body_bot, leg2_right, chara);
    joint = addJointBall(leg1_right->initialPosition->addY( legDimension.getY()/2 ), leg2_right, leg1_right, chara);
    joint = addJointBall(foot_right->initialPosition->addY( footDimension.getY()/2 ).addZ((legDimension.getZ()-footDimension.getZ())/2), leg1_right, foot_right, chara);

    joint = addJointBall(arm2_right->initialPosition->addY( armDimension.getY()/2 ).addX( armDimension.getX()/2 ), body_top, arm2_right, chara);
    joint = addJointBall(arm1_right->initialPosition->addY( armDimension.getY()/2 ), arm2_right, arm1_right, chara);
    joint = addJointBall(hand_right->initialPosition->addY( handDimension.getY()/2 ), arm1_right, hand_right, chara);

    joint = addJointBall(head->initialPosition->addY( -headDimension.getY()/2 ), body_top, head, chara);
    joint->setColor(MAT_CYAN);
    joint = addJointBall(body_bot->initialPosition->addY( +bodyDimension.getY()/4 ), body_bot, body_top, chara);
    joint->setColor(MAT_CYAN);

    //*/

    /*  ParticleEngine *PE;
    particleEngines.push_back( PE = new PESignal(2.5,30.0,0,15,this) );
    PE->material->setDiffuse(MAT_BLACK);*/
}

Scene::~Scene(){
    Physics::closeScene(this);

    if(externalForce != NULL){
        delete externalForce;
    }
    if(externalTorque != NULL){
        delete externalTorque;
    }

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
        Physics::createObject(obj, space, 1, position, NULL);
    }else{
        character->objects.push_back(obj);
        Physics::createObject(obj, character->space, 1, position, NULL);
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

void Scene::draw()
{
    for(std::vector<ParticleEngine*>::iterator it = particleEngines.begin(); it!= particleEngines.end(); it++){
        (*it)->tick();
    }

    camera->glApply();

    floor->draw();

    Material mat;
    Vector3f drawVec;

    for(std::list<Object*>::iterator it = selectedObjects.begin(); it!=selectedObjects.end(); it++){
        drawVec = *externalForce;
        mat.setDiffuse(MAT_MAGENTA);
        drawVec.realProductSelf(0.001);
        GLPrimitive::vector( drawVec , Physics::getObjectPosition((*it)), &mat);

        drawVec = *externalTorque;
        mat.setDiffuse(MAT_GREEN);
        drawVec.realProductSelf(0.001);
        GLPrimitive::vector( drawVec , Physics::getObjectPosition((*it)), &mat);
    }

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

    glDisable(GL_DEPTH_TEST);
    for(std::list<Object*>::iterator it = selectedObjects.begin(); it!=selectedObjects.end(); it++){
        (*it)->drawSelected();
    }
    glEnable(GL_DEPTH_TEST);
}

void Scene::simulationStep()
{
    for(int i=0;i<50;i++){
        for(std::list<Object*>::iterator it = selectedObjects.begin(); it!=selectedObjects.end(); it++){
            (*it)->appForce(externalForce);
            (*it)->appTorque(externalTorque);
        }

        if(interestJoint!=NULL){
            Physics::ControlPDBall(interestJoint->joint,tarQ,ks,kd);
        }

        Physics::simSingleStep(this);
    }
}
