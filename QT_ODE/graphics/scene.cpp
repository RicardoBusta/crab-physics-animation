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

    //mat.set(MAT_RED);
    mat.setDiffuse(MAT_DARK_CYAN);
    mat.gl();
    glPushMatrix();
    glTranslatef(200,0,0);
    GLPrimitive::sphere(120,0);
    glPopMatrix();

    //mat.set(MAT_GREEN);
    mat.setDiffuse(MAT_DARK_GREEN);
    mat.gl();
    glPushMatrix();
    glTranslatef(-200,0,0);
    GLPrimitive::box(100.0,100.0,100.0,0);
    glPopMatrix();

    //mat.set(MAT_BLUE);
    mat.setDiffuse(MAT_BLACK);
    mat.setEmission(MAT_GRAY_25);
    mat.gl();
    glPushMatrix();
    glTranslatef(-400,0,0);
    GLPrimitive::capsule(100,100,0);
    glPopMatrix();

    //mat.set(MAT_YELLOW);
    mat.setDiffuse(MAT_ORANGE);
    mat.gl();
    GLPrimitive::cylinder(100.0,100.0,0);
}
