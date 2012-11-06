#ifndef CONTROL_H
#define CONTROL_H

class Scene;

enum MOUSE_FUNCTION{MOUSE_FPS, MOUSE_ORBIT, MOUSE_FORCE, MOUSE_TORQUE};

class Control
{
public:
    Control(Scene *scene);
    Scene *scene;

    MOUSE_FUNCTION mouse;

    void rotateCamera( float rx, float ry );
    void moveCamera ( float mx, float my );
    void applyForce( float x, float y );
    void applyTorque( float x, float y );
};

#endif // CONTROL_H
