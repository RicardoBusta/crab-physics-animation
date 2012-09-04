#include "glprimitive.h"

#include <QtOpenGL>

void GLPrimitive::sphere(float r, float* rot){
    //draw sphere
    float angi = 360.0/10;
    float angj = 360.0/10;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
        }
    }
}

void GLPrimitive::box(float lx, float ly, float lz, float* rot){
    //draw box
    if(rot!=0){
        glMultMatrixf(rot);
    }
    glBegin(GL_QUADS);
    //front
    glColor3f(1,0,0);
    glVertex3f(-lx,-ly,+lz);
    glVertex3f(+lx,-ly,+lz);
    glVertex3f(+lx,+ly,+lz);
    glVertex3f(-lx,+ly,+lz);
    //back
    glColor3f(0,1,0);
    glVertex3f(-lx,-ly,-lz);
    glVertex3f(-lx,+ly,-lz);
    glVertex3f(+lx,+ly,-lz);
    glVertex3f(+lx,-ly,-lz);
    //left
    glColor3f(0,0,1);
    glVertex3f(-lx,-ly,-lz);
    glVertex3f(-lx,-ly,+lz);
    glVertex3f(-lx,+ly,+lz);
    glVertex3f(-lx,+ly,-lz);
    //right
    glColor3f(1,1,0);
    glVertex3f(+lx,-ly,-lz);
    glVertex3f(+lx,+ly,-lz);
    glVertex3f(+lx,+ly,+lz);
    glVertex3f(+lx,-ly,+lz);
    //top
    glColor3f(1,0,1);
    glVertex3f(-lx,+ly,-lz);
    glVertex3f(-lx,+ly,+lz);
    glVertex3f(+lx,+ly,+lz);
    glVertex3f(+lx,+ly,-lz);
    //bottom
    glColor3f(0,1,1);
    glVertex3f(-lx,-ly,-lz);
    glVertex3f(+lx,-ly,-lz);
    glVertex3f(+lx,-ly,+lz);
    glVertex3f(-lx,-ly,+lz);
    glEnd();
}
