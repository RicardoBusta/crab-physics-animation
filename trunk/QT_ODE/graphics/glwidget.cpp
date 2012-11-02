#include "glwidget.h"

#include <QMouseEvent>

#include "graphics/camera.h"
#include "control/control.h"

#ifdef DEBUG_MODE
#include <iostream>
using namespace std;
#endif

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    scene = new Scene(this);
    control = new Control(scene);

    connect(&simTimer, SIGNAL(timeout()), this, SLOT(simStep()));

    simTimer.start(1);
}

GLWidget::~GLWidget()
{
    if(scene!=NULL) delete scene;
    if(control!=NULL) delete control;
}

void GLWidget::bindShader(){
#ifdef SHADERS_ENABLED
    shaderProgram.bind();
#endif
}

void GLWidget::releaseShader(){
#ifdef SHADERS_ENABLED
    shaderProgram.release();
#endif
}

void GLWidget::initializeGL()
{
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glShadeModel(GL_SMOOTH);
#ifndef DEF_LINUX
    glEnable(GL_COLOR_MATERIAL);
#endif

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    static GLfloat light1pos[4] = { -0.892, 0.3, 0.9, 0.0 };
    static GLfloat light1diffuse[] = { 0.8f, 0.8f, 0.8, 1.0f };
    static GLfloat light1specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };

    static GLfloat light2pos[4] = { 0.588, 0.46, 0.248, 0.0 };
    static GLfloat light2diffuse[] = { 0.498f, 0.5f, 0.6, 1.0f };
    static GLfloat light2specular[] = { 0.2f, 0.2f, 0.2f, 1.0f };

    static GLfloat light3pos[4] = { 0.216, -0.392, -0.216, 0.0 };
    static GLfloat light3diffuse[] = { 0.798f, 0.838f, 1.0, 1.0f };
    static GLfloat light3specular[] = { 0.06f, 0.0f, 0.0f, 1.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glLightfv(GL_LIGHT0, GL_POSITION, light1pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light1diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light1specular);

    glLightfv(GL_LIGHT1, GL_POSITION, light2pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light2diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light2specular);

    glLightfv(GL_LIGHT2, GL_POSITION, light3pos);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light3diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light3specular);

#ifdef SHADERS_ENABLED
    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/phong.vert");
    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/phong.frag");
    //        shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/toon.vert");
    //       shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/toon.frag");
#endif
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    #ifdef SHADERS_ENABLED
    bindShader();
    #endif

    glPushMatrix();
    scene->draw();
    glPopMatrix();

    #ifdef SHADERS_ENABLED
    releaseShader();
    #endif
}

void GLWidget::resizeGL(int w, int h)
{
    int size = qMax(w,h);
    glViewport((w-size)/2, (h-size)/2, size, size);
    //glViewport(0,0,w,h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(0,w,0,h,1000,-1000);
    glFrustum(-1,1,-1,1,2.236,100000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    mousexy = event->pos();

    if(event->button() == Qt::LeftButton){
        mouseButton = 1;
    }else if(event->button() == Qt::RightButton){
        mouseButton = 2;
    }else{
        mouseButton = 0;
    }
}

#include "scene/object.h"

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    float mousex = (float) ( event->pos().x() - mousexy.x() );
    float mousey = (float) ( event->pos().y() - mousexy.y() );

    if(mouseButton==1){
        control->rotateCamera(mousex/100.0,mousey/100.0);
    }
    if(mouseButton==2){
        control->moveCamera(mousex/10.0,mousey/10.0);
    }

    mousexy = event->pos();

    scene->camera->updateMatrix();

    update();
}

void GLWidget::simStep(){
    scene->simulationStep();
    update();
}
