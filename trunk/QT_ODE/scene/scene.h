#ifndef SCENE_H
#define SCENE_H

class Camera;
class Object;

#include <vector>
#include "physics/physics.h"

//The scene where the objects are placed.
class Scene
{
public:
    Scene();
    ~Scene();

    WorldID world;
    SpaceID space;

    //Physics

    void simulationStep();

    //Graphics

    void draw();

    //Manipulate World

    void addObject(int shape, int diffuse, int specular, float prop1, float prop2, float prop3, float posx, float posy, float posz);

    //!make private
public:
    //Physics


    //Graphics

    Camera *camera;
    std::vector<Object*> objList;
};

#endif // SCENE_H
