#ifndef SCENE_H
#define SCENE_H

class Camera;

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
};

#endif // SCENE_H
