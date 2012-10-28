#include "particleengine.h"

#include "scene/scene.h"
#include "scene/particle.h"
#include "graphics/material.h"

ParticleEngine::ParticleEngine(float x, float y, float z, int timeout, Scene *scene)
{
    this->x = x;
    this->y = y;
    this->z = z;
    life = 0;
    this->scene = scene;
    this->timeout = timeout;
    material = new Material();
}

ParticleEngine::~ParticleEngine(){
    if(material!=NULL){
        delete material;
    }
}

void PESignal::tick(){
    if(life == 0){
        this->scene->addParticle(new PingParticle(this->x, this->y, this->z, 100, this->material, 0, 0, 0));
        life = timeout;
    }
    life --;
}
