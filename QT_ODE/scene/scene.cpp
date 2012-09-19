#include "scene.h"

#include <QtOpenGL>

#include "physics/physics.h"
#include "graphics/glprimitive.h"
#include "graphics/material.h"
#include "graphics/camera.h"

//TODO remove QtOpenGL include, and everything else as necessary.

Scene::Scene()
{
    Physics::init();
    camera = new Camera();

    camera->moveForward(-1000);
    camera->moveUp(200);
}

Scene::~Scene(){
    Physics::close();
    if(camera!=NULL){
        delete camera;
    }
}

void Scene::draw()
{
    camera->glApply();

    Material mat;

    glTranslatef(0,0,100);

    //mat.set(MAT_RED);
    mat.setDiffuse(MAT_MAGENTA);
    mat.setSpecular(MAT_WHITE);
    mat.gl();
    glPushMatrix();
    glTranslatef(200,0,0);
    GLPrimitive::sphere(120);
    glPopMatrix();

    //mat.set(MAT_GREEN);
    mat.setDiffuse(MAT_DARK_GREEN);
    mat.setSpecular(MAT_WHITE);
    mat.gl();
    glPushMatrix();
    glTranslatef(-200,0,0);
    GLPrimitive::box(100.0,100.0,100.0);
    glPopMatrix();

    //mat.set(MAT_BLUE);
    mat.setDiffuse(MAT_WHITE);
    mat.setSpecular(MAT_WHITE);
    //mat.setEmission(MAT_RED);
    mat.gl();
    glPushMatrix();
    glTranslatef(-400,0,0);
    GLPrimitive::capsule(100,100);
    glPopMatrix();

    //mat.set(MAT_YELLOW);
    mat.setDiffuse(MAT_ORANGE);
    mat.setSpecular(MAT_WHITE);
    mat.gl();
    GLPrimitive::cylinder(100.0,100.0);

    glTranslatef(0,0,-400);

    mat.setDiffuse(MAT_RED);
//    mat.setDiffuse(MAT_BLUE);
    mat.setSpecular(MAT_WHITE);
    mat.gl();
    glPushMatrix();
    glTranslatef(200,0,0);
    GLPrimitive::sphere(120);
    glPopMatrix();

    mat.setDiffuse(MAT_GREEN);
//    mat.setDiffuse(MAT_DARK_GREEN);
    mat.setSpecular(MAT_WHITE);
    mat.gl();
    glPushMatrix();
    glTranslatef(-200,0,0);
    GLPrimitive::box(100.0,100.0,100.0);
    glPopMatrix();

    mat.setDiffuse(MAT_BLUE);
//    mat.setDiffuse(MAT_WHITE);
    mat.setSpecular(MAT_WHITE);
    //mat.setEmission(MAT_RED);
    mat.gl();
    glPushMatrix();
    glTranslatef(-400,0,0);
    GLPrimitive::capsule(100,100);
    glPopMatrix();

    mat.setDiffuse(MAT_YELLOW);
//    mat.setDiffuse(MAT_ORANGE);
    mat.setSpecular(MAT_WHITE);
    mat.gl();
    GLPrimitive::cylinder(100.0,100.0);
}
