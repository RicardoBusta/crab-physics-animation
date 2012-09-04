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
    GLPrimitive::box(200.0,200.0,200.0,0);
}
