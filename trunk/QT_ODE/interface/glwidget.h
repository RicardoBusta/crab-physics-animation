#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "../graphics/scene.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    Scene *scene;

signals:
    
public slots:
    
};

#endif // GLWIDGET_H
