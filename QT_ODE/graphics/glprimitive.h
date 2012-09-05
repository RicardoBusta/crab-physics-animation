#ifndef GLPRIMITIVE_H
#define GLPRIMITIVE_H

//Draws the primitives using opengl commands.
namespace GLPrimitive
{
    void sphere(float r, float* rot=0);
    void box(float lx, float ly, float lz, float* rot=0);
    void cylinder(float r, float l);
    void capsule(float r, float l);

    //future implementation
    //void triMesh();
    //void convexHull();

    //not tied to any object
    //part of the static world
    void plane(float a, float b, float c, float d);

    //don't represent a solid object
    //start at the object center and go to z direction
    void ray(float length);
}

#endif // GLPRIMITIVE_H
