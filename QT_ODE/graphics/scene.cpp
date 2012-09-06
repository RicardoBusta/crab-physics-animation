#include "scene.h"

#include <QtOpenGL>

#include "physics/physics.h"
#include "glprimitive.h"

#include "material.h"

Scene::Scene()
{
    Physics::init();
}

Scene::~Scene(){
    Physics::close();
}

void Scene::draw()
{
    Material mat;
    mat.set(MAT_RED);
    mat.gl();
    GLPrimitive::sphere(120,0);

    mat.set(MAT_GREEN);
    mat.gl();
    GLPrimitive::box(100.0,100.0,100.0,0);

    mat.set(MAT_BLUE);
    mat.gl();

    GLPrimitive::capsule(100,100,0);
}
