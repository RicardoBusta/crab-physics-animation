#ifndef GLFRAME_H
#define GLFRAME_H

#include <QWidget>
#include "glwidget.h"

class GLFrame : public QWidget
{
    Q_OBJECT
public:
    explicit GLFrame(QWidget *parent = 0);
    ~GLFrame();
    
private:
    void resizeEvent(QResizeEvent *);

    GLWidget *glwidget;

signals:
    
public slots:
    
};

#endif // GLFRAME_H
