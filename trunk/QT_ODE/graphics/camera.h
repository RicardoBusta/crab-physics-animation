#ifndef CAMERA_H
#define CAMERA_H

class Vector3f;
class Matrix4f;

class Camera
{
public:
    Camera();
    ~Camera();

    void glApply();
    void updateMatrix();

    void moveForward(float amount);
    void moveBackward(float amount);
    void moveHorz(float amount);
    void moveVert(float amount);
public:
    Vector3f *posAt;
    Vector3f *lookAt;
    Vector3f *up;

    Matrix4f *matrix;
};

#endif // CAMERA_H
