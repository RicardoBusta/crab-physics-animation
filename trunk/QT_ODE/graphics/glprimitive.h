#ifndef GLPRIMITIVE_H
#define GLPRIMITIVE_H

//Draws the primitives using opengl commands.
namespace GLPrimitive
{
    void sphere(float r, float* rot=0);
    void box(float lx, float ly, float lz, float* rot=0);
    void cylinder();
    void capsule();
    void plane();
    void ray();
    void triMesh();
    void convexHull();
}

#endif // GLPRIMITIVE_H
