#include "glwidget.h"

#include <QMouseEvent>

#include <iostream>
using namespace std;

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    scene = new Scene();

    xrot = 0;
    yrot = 0;
}

GLWidget::~GLWidget()
{
    if(scene!=NULL) delete scene;
}

void GLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
//    glFrontFace(GL_CW);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
//    glEnable(GL_PROGRAM_POINT_SIZE);
//    glEnable(GL_NORMALIZE);

    //glEnable(GL_MULTISAMPLE);
    //if (!format().sampleBuffers())
    //{
      //  cout <<"OpenGL samplebuffers: This system does not have sample buffer support." << endl;

//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        glEnable(GL_POINT_SMOOTH);
//        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
//        glEnable(GL_LINE_SMOOTH);
//        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    //}

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

    static GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS, 128);


    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/vshader.vert");
    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/fshader.frag");
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0,0,-500);

    glRotatef(xrot,1,0,0);
    glRotatef(yrot,0,1,0);

    shaderProgram.bind();
    scene->draw();
    shaderProgram.release();
}

void GLWidget::resizeGL(int w, int h)
{
    int size = qMax(w,h);
    //glViewport(0,0,w,h);
    glViewport((w-size)/2, (h-size)/2, size, size);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(0,w,0,h,1000,-1000);
    glFrustum(-1,1,-1,1,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void GLWidget::mousePressEvent(QMouseEvent *event)
{

    mousexy = event->pos();

    if(event->button() == Qt::LeftButton){
        mouseButton = 1;
    }else{
        mouseButton = 0;
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int mousey = event->pos().x() - mousexy.x();
    int mousex = event->pos().y() - mousexy.y();

    if(mouseButton==1){
        xrot += (float)mousex/3;
        yrot += (float)mousey/3;
    }

    mousexy = event->pos();

    update();
}
