#include "particle.h"

#include <QtOpenGL>

#include "graphics/glutil.h"
#include "graphics/material.h"

void Particle::behave(){
    glPushMatrix();
    glTranslated(this->x, this->y, this->z);
    GLUtil::glSphereBillBoard();

    material->gl();

    if(alive){
        glNormal3f(0,0,1);
        particleLoop();
        life--;

        if(life <= 0){
            alive = false;
        }
    }
    glPopMatrix();
}

PingParticle::PingParticle(float x, float y, float z, int life, Material *material, float sx, float sy, float sz):Particle(x,y,z,life, material)
{
    this->sx = sx;
    this->sy = sy;
    this->sz = sz;
}

void PingParticle::particleLoop(){
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<36;i++){
            glVertex3f(life*cos(i*M_PI/18)/5, life*sin(i*M_PI/18)/5, 0 );

        }
        glVertex3f(life*cos( (0)*M_PI/18)/5, life*sin( (0)*M_PI/18)/5, 0 );
        glEnd();
    this->x += sx;
    this->y += sy;
    this->z += sz;
}
