#include "prop.h"

#include "graphics/glprimitive.h"

#include "graphics/material.h"

Prop::Prop(Scene *scene, PROP_TYPE type)
{
    this->scene = scene;
    this->type = type;

    mat = new Material();
    mat->setDiffuse(MAT_GRAY_75);
}

Prop::~Prop(){
    if(mat!=0){
        delete mat;
    }
}

void Prop::draw()
{
    switch(type){
        case PROP_PLANE:
            GLPrimitive::floor(5000,mat);
            break;
        default:
            break;
    }
}
