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
    mat.gl();

    GLPrimitive::box(100.0,100.0,100.0,0);

    GLPrimitive::sphere(120,0);
}
