#ifndef SCENE_H
#define SCENE_H

class Camera;
class Object;
class Particle;
class ParticleEngine;
class Vector3f;
class GLWidget;
class Character;
class Prop;

#include <vector>
#include <list>
#include <QString>
#include "physics/physics.h"

//The scene where the objects are placed.
class Scene
{
public:
    GLWidget *parent;

    Scene(GLWidget *parent);
    ~Scene();

    WorldID world;
    //TopLevelSpace
    SpaceID space;
    JointGroupID contactGroup;

    //Physics

    void simulationStep();

    //Graphics

    void draw();

    Prop *floor;

    Joint *interestJoint;

    Vector3f *externalForce;
    Vector3f *externalTorque;

    //Manipulate World

    Object* addObject(int shape, int diffuse, Character* character, Vector3f properties, Vector3f position);
    Joint * addJointBall(Vector3f anchor, Object *parent, Object *child, Character *chara);
    void addParticle(Particle* particle);


    //XML
    void loadFile(QString filename);
    void saveFile(QString filename);

    //!make private
public:
    //Physics


    //Graphics

    Camera *camera;
    std::vector<Object*> objects;
    std::vector<Character*> characters;
    //std::vector<Contact*> contacts;
    std::list<Particle*> particles;
    std::vector<ParticleEngine*> particleEngines;
    std::list<Object*> selectedObjects;
};

#endif // SCENE_H
