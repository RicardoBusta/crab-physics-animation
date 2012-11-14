#include "object.h"

#include "graphics/glprimitive.h"
#include "math/matrix4f.h"
#include "math/vector3f.h"
#include "graphics/material.h"

#include <QtOpenGL>
#include "graphics/glutil.h"

#include "scene/scene.h"
#include "graphics/camera.h"

Object::Object(Scene *scene)
{
    this->scene = scene;

    transform = new Matrix4f();
    transform->setIdentity();

    initialPosition = new Vector3f();

    material = new Material();
}

Object::~Object(){
    if(transform!=NULL){
        delete transform;
    }
    if(material!=NULL){
        delete material;
    }
    if(initialPosition!=NULL){
        delete initialPosition;
    }
}

void Object::appTorque(float x, float y, float z){
    Physics::bodyAddTorque(body,x,y,z);
}

void Object::appTorque(Vector3f *torque)
{
    Physics::bodyAddTorque(body, torque->getX(), torque->getY(), torque->getZ());
}

void Object::appForce(float x, float y, float z){
    Physics::bodyAddForce(body,x,y,z);
}

void Object::appForce(Vector3f *force)
{
    Physics::bodyAddForce(body, force->getX(), force->getY(), force->getZ());
}

void Object::draw(){
    Physics::getGeomTransform(geometry, transform);

    switch(shape){
        case OBJ_BOX:
            GLPrimitive::box(properties[0],properties[1],properties[2], material, transform);
            break;
        case OBJ_SPHERE:
            GLPrimitive::sphere(properties[0], material, transform);
            break;
        case OBJ_CYLINDER:
            GLPrimitive::cylinder(properties[0], properties[1], material, transform);
            break;
        case OBJ_CAPSULE:
            GLPrimitive::capsule(properties[0],properties[1], material, transform);
            break;
        default:
            break;
    }
}


void Object::drawSelected(){
    Physics::getGeomTransform(geometry, transform);

    Vector3f normal = scene->camera->forward->realProduct(-1);

    glDisable(GL_DEPTH_TEST);
    switch(shape){
        case OBJ_BOX:
            material->glInverse();
            glNormal3f(normal.getX(), normal.getY(), normal.getZ()) ;
            GLPrimitive::wire_box(properties[0],properties[1],properties[2], 0, transform);
            break;
        case OBJ_SPHERE:
            glPushMatrix();
            glTranslatef(transform->getPosX(), transform->getPosY(), transform->getPosZ());
            GLUtil::glSphereBillBoard();
            material->glInverse();
            glNormal3f(normal.getX(), normal.getY(), normal.getZ()) ;
            GLPrimitive::bb_circle( properties[0], 0 );
            glPopMatrix();
//            GLPrimitive::wire_sphere(properties[0], material, transform);
            break;
        case OBJ_CYLINDER:
            material->glInverse();
            glNormal3f(normal.getX(), normal.getY(), normal.getZ()) ;
            GLPrimitive::wire_cylinder(properties[0], properties[1], 0, transform);
            break;
        case OBJ_CAPSULE:
            material->glInverse();
            glNormal3f(normal.getX(), normal.getY(), normal.getZ()) ;
            GLPrimitive::wire_capsule(properties[0],properties[1], 0, transform);
            break;
        default:
            break;
    }
    glEnable(GL_DEPTH_TEST);
}
