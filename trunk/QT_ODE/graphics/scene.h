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

    Camera *camera;
private:

};

#endif // SCENE_H
