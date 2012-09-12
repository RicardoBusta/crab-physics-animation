#include "camera.h"

#include <QtOpenGL>

#include "../math/vector3f.h"
#include "../math/matrix4f.h"

#ifdef DEBUG_MODE
#include <iostream>
using namespace std;
#endif

Camera::Camera()
{
    posAt = new Vector3f( 0.0, 30.0, 100.0 );
    lookAt = new Vector3f( 0.0, 0.0, -1.0 );
    up = new Vector3f( 0.0, 1.0, 0.0 );
    matrix = new Matrix4f();

    updateMatrix();
}

Camera::~Camera(){
    if(posAt!=NULL){
        delete posAt;
    }
    if(lookAt!=NULL){
        delete lookAt;
    }
    if(up!=NULL){
        delete up;
    }
    if(matrix!=NULL){
        delete matrix;
    }
}

void Camera::updateMatrix()
{
    Vector3f *forward = new Vector3f();
    Vector3f *side = new Vector3f();
    Vector3f *newUp = new Vector3f();

    cout << "posAt ";
    posAt->stdPrint();
    cout << "lookAt ";
    lookAt->stdPrint();
    cout << "up ";
    up->stdPrint();


    //---------------------------------
    //forward = lookAt - posAt (the direction you are looking)
    forward->set( lookAt->subtract( posAt ) );
    forward->normalize();
    cout << "forward ";
    forward->stdPrint();
    //---------------------------------
    //side = forward x up - (a vector pointing to the side)
    side->set( forward->crossProduct( up ) );
    side->normalize();
    cout << "side ";
    side->stdPrint();
    //---------------------------------
    //recompute up = side x forward (new up with the camera tilt)
    newUp->set( side->crossProduct( forward ) );
    cout << "newUp";
    newUp->stdPrint();
    //---------------------------------
    matrix->set( 0, side->getX() );
    matrix->set( 4, side->getY() );
    matrix->set( 8, side->getZ() );
    matrix->set(12, 0.0);
    //------------------
    matrix->set( 1, newUp->getX() );
    matrix->set( 5, newUp->getY() );
    matrix->set( 9, newUp->getZ() );
    matrix->set(13, 0.0);
    //------------------
    matrix->set( 2, -forward->getX() );
    matrix->set( 6, -forward->getY() );
    matrix->set(10, -forward->getZ() );
    matrix->set(14, 0.0);
    //------------------
    matrix->set( 3, 0.0);
    matrix->set( 7, 0.0);
    matrix->set(11, 0.0);
    matrix->set(15, 1.0);
    //------------------

    delete forward;
    delete side;
    delete newUp;
}

void Camera::glApply(){
    glLoadIdentity();
    float matrix4f[16];
    matrix->get(matrix4f);
    matrix->stdPrint();
    glTranslatef(-posAt->getX(), -posAt->getY(), -posAt->getZ());
    glMultMatrixf(matrix4f);
    //glScalef(-1,0,0);
}

void Camera::moveForward(float amount)
{
}

void Camera::moveBackward(float amount)
{
    Vector3f *forward = new Vector3f();

    forward->set( lookAt->subtract( posAt ) );
    forward->set( forward->realProduct( amount ) );
    posAt->set ( posAt->subtract(forward) );
    lookAt->set ( lookAt->subtract(forward) );

    delete forward;
}

void Camera::moveHorz(float amount)
{
    Vector3f *side = new Vector3f(1,0,0);

    side->set( side->realProduct( amount ) );
    posAt->set ( posAt->subtract(side) );
    //lookAt->set ( lookAt->subtract(side) );

    delete side;
}

void Camera::moveVert(float amount)
{
    Vector3f *side = new Vector3f(0,1,0);

    side->set( side->realProduct( amount ) );
    posAt->set ( posAt->subtract(side) );
    //lookAt->set ( lookAt->subtract(side) );

    delete side;
}
