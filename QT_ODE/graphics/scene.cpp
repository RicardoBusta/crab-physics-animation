#include "scene.h"

#include <QtOpenGL>

#include "physics/physics.h"
#include "glprimitive.h"

Scene::Scene()
{
    Physics::init();
}

Scene::~Scene(){
    Physics::close();
}

void Scene::draw()
{
    //GLPrimitive::box(100.0,100.0,100.0,0);
    GLPrimitive::sphere(100,0);
}
