#include "glprimitive.h"

#include <QtOpenGL>

#define PI180 0.017453292519943295769
#define CIRC_DIV 20

void GLPrimitive::sphere(float r, float* rot){
    //draw sphere

    float angi = PI180*360.0/CIRC_DIV;
    float angj = PI180*360.0/CIRC_DIV;
    float ai1,ai2,aj1,aj2,x,y,z;

    for(int i=0;i<CIRC_DIV/2;i++){
        ai1 = angi*i+90;
        ai2 = angi*(i+1)+90;
        for(int j=0;j<CIRC_DIV;j++){
            aj1 = angj*j;
            aj2 = angj*(j+1);

            glBegin(GL_QUADS);
            x = cos(ai1)*cos(aj1);
            y = sin(ai1);
            z = cos(ai1)*sin(aj1);
            glNormal3f(x,y,z);
            glVertex3f(r*x,r*y,r*z);
            x = cos(ai1)*cos(aj2);
            z = cos(ai1)*sin(aj2);
            glNormal3f(x,y,z);
            glVertex3f(r*x,r*y,r*z);
            x = cos(ai2)*cos(aj2);
            y = sin(ai2);
            z = cos(ai2)*sin(aj2);
            glNormal3f(x,y,z);
            glVertex3f(r*x,r*y,r*z);
            x = cos(ai2)*cos(aj1);
            z = cos(ai2)*sin(aj1);
            glNormal3f(x,y,z);
            glVertex3f(r*x,r*y,r*z);
            glEnd();

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
    glNormal3f(0,0,+1);
    glVertex3f(-lx,-ly,+lz);
    glVertex3f(+lx,-ly,+lz);
    glVertex3f(+lx,+ly,+lz);
    glVertex3f(-lx,+ly,+lz);
    //back
    glNormal3f(0,0,-1);
    glVertex3f(-lx,-ly,-lz);
    glVertex3f(-lx,+ly,-lz);
    glVertex3f(+lx,+ly,-lz);
    glVertex3f(+lx,-ly,-lz);
    //left
    glNormal3f(-1,0,0);
    glVertex3f(-lx,-ly,-lz);
    glVertex3f(-lx,-ly,+lz);
    glVertex3f(-lx,+ly,+lz);
    glVertex3f(-lx,+ly,-lz);
    //right
    glNormal3f(+1,0,0);
    glVertex3f(+lx,-ly,-lz);
    glVertex3f(+lx,+ly,-lz);
    glVertex3f(+lx,+ly,+lz);
    glVertex3f(+lx,-ly,+lz);
    //top
    glNormal3f(0,+1,0);
    glVertex3f(-lx,+ly,-lz);
    glVertex3f(-lx,+ly,+lz);
    glVertex3f(+lx,+ly,+lz);
    glVertex3f(+lx,+ly,-lz);
    //bottom
    glNormal3f(0,-1,0);
    glVertex3f(-lx,-ly,-lz);
    glVertex3f(+lx,-ly,-lz);
    glVertex3f(+lx,-ly,+lz);
    glVertex3f(-lx,-ly,+lz);
    glEnd();
}
