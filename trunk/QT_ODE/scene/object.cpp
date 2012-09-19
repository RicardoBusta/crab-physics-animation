#include "object.h"

#include "graphics/glprimitive.h"

Object::Object()
{
}

void Object::draw(){
    material.gl();

    switch(shape){
    case OBJ_BOX:
        GLPrimitive::box(properties[0],properties[1],properties[2]);
        break;
    }
}
