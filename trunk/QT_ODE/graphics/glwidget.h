#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "scene/scene.h"
#include "control/control.h"

#include <QGLShaderProgram>
#include <QTimer>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    void bindShader();
    void releaseShader();

    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

private:
    Scene *scene;
    Control *control;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    QPoint mousexy;
    int mouseButton;

    QTimer simTimer;

#ifdef SHADERS_ENABLED
    QGLShaderProgram shaderProgram;
#endif

signals:
    
public slots:

private slots:
    void simStep();
    
};

#endif // GLWIDGET_H
