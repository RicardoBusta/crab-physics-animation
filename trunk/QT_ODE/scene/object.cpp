#include "object.h"

#include "graphics/glprimitive.h"
#include "math/matrix4f.h"
#include "math/vector3f.h"
#include "graphics/material.h"

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

void Object::appForce(float x, float y, float z){
    Physics::bodyAddForce(body,x,y,z);
}

void Object::draw(){
    if(shape!= OBJ_PLANE){
        Physics::getGeomTransform(geometry, transform);
    }

    switch(shape){
    case OBJ_PLANE:
        GLPrimitive::plane(properties[0], material, transform);
        break;
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
