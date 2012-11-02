#ifndef CONTROL_H
#define CONTROL_H

class Scene;

class Control
{
public:
    Control(Scene *scene);
    Scene *scene;

    void rotateCamera( float rx, float ry );
    void moveCamera ( float mx, float my );
};

#endif // CONTROL_H
