#include "object.h"

#include "graphics/glprimitive.h"
#include "math/matrix4f.h"
#include "graphics/material.h"

Object::Object()
{
    transform = new Matrix4f();
    transform->setIdentity();

    material = new Material();
}

Object::~Object(){
    if(transform!=NULL){
        delete transform;
    }
    if(material!=NULL){
        delete material;
    }
}

void Object::draw(){   
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
    case OBJ_CYL:
        GLPrimitive::cylinder(properties[0], properties[1], material, transform);
        break;
    case OBJ_CAP:
        GLPrimitive::capsule(properties[0],properties[1], material, transform);
        break;
    default:
        break;
    }
}
