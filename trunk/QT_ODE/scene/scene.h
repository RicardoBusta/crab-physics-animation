#ifndef SCENE_H
#define SCENE_H

class Camera;
class Object;

//The scene where the objects are placed.
class Scene
{
public:
    Scene();
    ~Scene();

    void draw();

    void addObject(/*todo, shape and properties like color, mass etc*/);

public:
    Camera *camera;

    Object *objectList[100];
};

#endif // SCENE_H
