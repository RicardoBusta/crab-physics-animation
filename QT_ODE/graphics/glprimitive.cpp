#include "glprimitive.h"

#include <QtOpenGL>

#include "iostream"
using namespace std;

void GLPrimitive::sphere(float r, float* rot){
    //draw sphere
}

void GLPrimitive::box(float lx, float ly, float lz, float* rot){
    //draw box
    if(rot!=0){
        glMultMatrixf(rot);
    }
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(200,0,0);
    glVertex3f(200,200,0);
    glVertex3f(0,200,0);
    glEnd();
    glBegin(GL_QUADS);
    //front
    cout << lx << ly << lz << endl;
    glVertex3f(-lx,-ly,+lz);
    glVertex3f(+lx,-ly,+lz);
    glVertex3f(+lx,+ly,+lz);
    glVertex3f(-lx,+ly,+lz);
    //back
    glVertex3f(-lx,-ly,-lz);
    glVertex3f(-lx,+ly,-lz);
    glVertex3f(+lx,+ly,-lz);
    glVertex3f(+lx,-ly,-lz);
    //left
    glVertex3f(-lx,-ly,-lz);
    glVertex3f(-lx,-ly,+lz);
    glVertex3f(-lx,+ly,+lz);
    glVertex3f(-lx,+ly,-lz);
    //right
    glVertex3f(+lx,-ly,-lz);
    glVertex3f(+lx,+ly,-lz);
    glVertex3f(+lx,+ly,+lz);
    glVertex3f(+lx,-ly,+lz);
    //top
    glVertex3f(-lx,+ly,-lz);
    glVertex3f(-lx,+ly,+lz);
    glVertex3f(+lx,+ly,+lz);
    glVertex3f(+lx,+ly,-lz);
    //bottom
    glVertex3f(-lx,-ly,-lz);
    glVertex3f(+lx,-ly,-lz);
    glVertex3f(+lx,-ly,+lz);
    glVertex3f(-lx,-ly,+lz);
    glEnd();
}
