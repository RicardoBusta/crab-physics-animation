#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "../graphics/scene.h"

#include <QGLShaderProgram>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();



private:
    Scene *scene;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    QPoint mousexy;
    int mouseButton;

    float rotx, roty;

    QGLShaderProgram shaderProgram;


signals:
    
public slots:
    
};

#endif // GLWIDGET_H
