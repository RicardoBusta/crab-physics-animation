#ifndef SCENE_H
#define SCENE_H

class Camera;
class Object;
class Particle;
class ParticleEngine;
class Vector3f;
class GLWidget;

#include <vector>
#include <list>
#include "physics/physics.h"

//The scene where the objects are placed.
class Scene
{
public:
    GLWidget *parent;

    Scene(GLWidget *parent);
    ~Scene();

    WorldID world;
    SpaceID space;

    //Physics

    void simulationStep();

    //Graphics

    void draw();

    //Manipulate World

    Object* addObject(int shape, int diffuse, int specular, float prop1, float prop2, float prop3, Vector3f position);
    void addParticle(Particle* particle);

    //!make private
public:
    //Physics


    //Graphics

    Camera *camera;
    std::vector<Object*> objects;
    std::list<Particle*> particles;
    std::vector<ParticleEngine*> particleEngines;

    Object *testObject;
};

#endif // SCENE_H
