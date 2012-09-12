#include "scene.h"

#include <QtOpenGL>

#include "physics/physics.h"
#include "glprimitive.h"
#include "material.h"
#include "camera.h"

Scene::Scene()
{
    Physics::init();
    camera = new Camera();
}

Scene::~Scene(){
    Physics::close();
    if(camera!=NULL){
        delete camera;
    }
}

void Scene::draw()
{

    Material mat;

    //mat.set(MAT_RED);
    mat.setDiffuse(MAT_BLUE);
    mat.setSpecular(MAT_WHITE);
    mat.gl();
    glPushMatrix();
    glTranslatef(200,0,0);
    GLPrimitive::sphere(120,0);
    glPopMatrix();

    //mat.set(MAT_GREEN);
    mat.setDiffuse(MAT_DARK_GREEN);
    mat.setSpecular(MAT_WHITE);
    mat.gl();
    glPushMatrix();
    glTranslatef(-200,0,0);
    GLPrimitive::box(100.0,100.0,100.0,0);
    glPopMatrix();

    //mat.set(MAT_BLUE);
    mat.setDiffuse(MAT_WHITE);
    mat.setSpecular(MAT_WHITE);
    //mat.setEmission(MAT_RED);
    mat.gl();
    glPushMatrix();
    glTranslatef(-400,0,0);
    GLPrimitive::capsule(100,100,0);
    glPopMatrix();

    //mat.set(MAT_YELLOW);
    mat.setDiffuse(MAT_ORANGE);
    mat.setSpecular(MAT_WHITE);
    mat.gl();
    GLPrimitive::cylinder(100.0,100.0,0);
}
