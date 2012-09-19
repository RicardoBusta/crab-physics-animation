#include "scene.h"

#include <QtOpenGL>

#include "physics/physics.h"
#include "graphics/glprimitive.h"
#include "graphics/material.h"
#include "graphics/camera.h"
#include "math/matrix4f.h"
#include "scene/object.h"

//TODO remove QtOpenGL include, and everything else as necessary.

Scene::Scene()
{
    Physics::init();
    camera = new Camera();

    camera->moveForward(-2000);
    camera->moveUp(200);

    for(int i=0;i<100;i++){
        objectList[i]=NULL;
    }

    objectList[0] = new Object();
    objectList[0]->shape = OBJ_PLANE;
    objectList[0]->material->setDiffuse(MAT_GRAY_75);
    objectList[0]->material->setSpecular(MAT_WHITE);
    objectList[0]->transform->translate(-2500,-100,-2500);
    objectList[0]->properties[0] = 5000;

    objectList[1] = new Object();
    objectList[1]->shape = OBJ_SPHERE;
    objectList[1]->material->setDiffuse(MAT_MAGENTA);
    objectList[1]->material->setSpecular(MAT_WHITE);
    objectList[1]->transform->translate(200,0,100);
    objectList[1]->properties[0] = 100;

    objectList[2] = new Object();
    objectList[2]->shape = OBJ_BOX;
    objectList[2]->material->setDiffuse(MAT_DARK_GREEN);
    objectList[2]->material->setSpecular(MAT_WHITE);
    objectList[2]->transform->translate(-200,0,100);
    objectList[2]->properties[0] = 100;
    objectList[2]->properties[1] = 100;
    objectList[2]->properties[2] = 100;

    objectList[3] = new Object();
    objectList[3]->shape = OBJ_BOX;
    objectList[3]->material->setDiffuse(MAT_ORANGE);
    objectList[3]->material->setSpecular(MAT_WHITE);
    objectList[3]->transform->translate(200,0,-300);
    objectList[3]->properties[0] = 100;
    objectList[3]->properties[1] = 100;
    objectList[3]->properties[2] = 100;

    objectList[4] = new Object();
    objectList[4]->shape = OBJ_SPHERE;
    objectList[4]->material->setDiffuse(MAT_BLUE);
    objectList[4]->material->setSpecular(MAT_WHITE);
    objectList[4]->transform->translate(-200,0,-300);
    objectList[4]->properties[0] = 100;

    objectList[5] = new Object();
    objectList[5]->shape = OBJ_CYL;
    objectList[5]->material->setDiffuse(MAT_YELLOW);
    objectList[5]->material->setSpecular(MAT_WHITE);
    objectList[5]->transform->translate(-500,0,-300);
    objectList[5]->properties[0] = 100;
    objectList[5]->properties[1] = 200;

    objectList[6] = new Object();
    objectList[6]->shape = OBJ_CYL;
    objectList[6]->material->setDiffuse(MAT_WHITE);
    objectList[6]->material->setSpecular(MAT_WHITE);
    objectList[6]->transform->translate(-500,0,100);
    objectList[6]->properties[0] = 100;
    objectList[6]->properties[1] = 200;

    objectList[7] = new Object();
    objectList[7]->shape = OBJ_CAP;
    objectList[7]->material->setDiffuse(MAT_BLACK);
    objectList[7]->material->setSpecular(MAT_WHITE);
    objectList[7]->transform->translate(-700,0,100);
    objectList[7]->properties[0] = 100;
    objectList[7]->properties[1] = 200;
}

Scene::~Scene(){
    Physics::close();
    if(camera!=NULL){
        delete camera;
    }

    for(int i=0;i<100;i++){
        if(objectList[i]!=NULL){
            delete objectList[i];
        }
    }
}

void Scene::draw()
{
    camera->glApply();

    for(int i=0;i<100;i++){
        if(objectList[i]!=NULL){
            objectList[i]->draw();
        }
    }

    /*

    //mat.set(MAT_GREEN);
    mat.setDiffuse(MAT_DARK_GREEN);
    mat.setSpecular(MAT_WHITE);

    glPushMatrix();
    glTranslatef(-200,0,0);
    GLPrimitive::box(100.0,100.0,100.0, &mat, identity);
    glPopMatrix();

    //mat.set(MAT_BLUE);
    mat.setDiffuse(MAT_WHITE);
    mat.setSpecular(MAT_WHITE);
    //mat.setEmission(MAT_RED);

    glPushMatrix();
    glTranslatef(-400,0,0);
    GLPrimitive::capsule(100,100, &mat, identity);
    glPopMatrix();

    //mat.set(MAT_YELLOW);
    mat.setDiffuse(MAT_ORANGE);
    mat.setSpecular(MAT_WHITE);

    GLPrimitive::cylinder(100.0,100.0, &mat, identity);

    glTranslatef(0,0,-400);

    mat.setDiffuse(MAT_RED);
//    mat.setDiffuse(MAT_BLUE);
    mat.setSpecular(MAT_WHITE);

    glPushMatrix();
    glTranslatef(200,0,0);
    GLPrimitive::sphere(120, &mat, identity);
    glPopMatrix();

    mat.setDiffuse(MAT_GREEN);
//    mat.setDiffuse(MAT_DARK_GREEN);
    mat.setSpecular(MAT_WHITE);

    glPushMatrix();
    glTranslatef(-200,0,0);
    GLPrimitive::box(100.0,100.0,100.0, &mat, identity);
    glPopMatrix();

    mat.setDiffuse(MAT_BLUE);
//    mat.setDiffuse(MAT_WHITE);
    mat.setSpecular(MAT_WHITE);
    //mat.setEmission(MAT_RED);

    glPushMatrix();
    glTranslatef(-400,0,0);
    GLPrimitive::capsule(100,100, &mat, identity);
    glPopMatrix();

    mat.setDiffuse(MAT_YELLOW);
//    mat.setDiffuse(MAT_ORANGE);
    mat.setSpecular(MAT_WHITE);

    GLPrimitive::cylinder(100.0,100.0, &mat, identity);

    delete identity;*/
}
