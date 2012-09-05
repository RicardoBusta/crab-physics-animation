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
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    float lspecular[] = {0.3,0.3,0.3,1.0};
    float lambient[] = {0.5,0.5,0.5,1.0};
    float ldiffuse[] = {0.8,0.8,0.8,1.0};
    float lposition[] = {0,0,0,1.0};

    glLightfv(GL_LIGHT0, GL_SPECULAR, lspecular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ldiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, lposition);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0,0,-500);

    glRotatef(xrot,1,0,0);
    glRotatef(yrot,0,1,0);

    scene->draw();
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
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int mousey = event->pos().x() - mousexy.x();
    int mousex = event->pos().y() - mousexy.y();

    xrot += (float)mousex/3;
    yrot += (float)mousey/3;

    mousexy = event->pos();

    update();
}
