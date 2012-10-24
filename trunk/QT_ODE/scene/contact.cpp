#include "contact.h"

#include "graphics/glprimitive.h"

#include "graphics/material.h"
#include "math/matrix4f.h"

Contact::Contact(float x, float y, float z)
{
    mat = new Material();
    mat->setDiffuse(MAT_RED);
    mat->setSpecular(MAT_WHITE);

    tr = new Matrix4f();
    tr->setIdentity();
    tr->translate(x,y,z);
}

Contact::~Contact(){
    delete mat;
    delete tr;
}

void Contact::draw()
{
    GLPrimitive::sphere(50,mat,tr);
}
