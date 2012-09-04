#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    scene = new Scene();
}

GLWidget::~GLWidget()
{
    if(scene!=NULL) delete scene;
}

void GLWidget::initializeGL()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);


}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //glColor3f(1,1,1);
    scene->draw();
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,w,0,h,1000,-1000);
    //glFrustum(-1,1,-1,1,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
