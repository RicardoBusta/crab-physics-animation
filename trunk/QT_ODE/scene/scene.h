#ifndef SCENE_H
#define SCENE_H

class Camera;
class Object;

#include <vector>

//The scene where the objects are placed.
class Scene
{
public:
    Scene();
    ~Scene();

    void simulation();

    void draw();

    void addObject(/*todo, shape and properties like color, mass etc*/);

public:
    Camera *camera;

    std::vector<Object*> objList;
};

#endif // SCENE_H
