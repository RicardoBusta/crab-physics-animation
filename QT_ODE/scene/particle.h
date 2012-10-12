#ifndef PARTICLE_H
#define PARTICLE_H

class Material;

class Particle
{
public:
    Particle(float x, float y, float z, int life, Material *material){
        this->x = x;
        this->y = y;
        this->z = z;
        this->life = life;
        this->material = material;
        alive = true;
    }

    float x, y, z;
    int life;

    bool alive;

    Material *material;

    void behave();

    virtual void particleLoop()=0;
};

class PingParticle:public Particle
{
public:
    float sx, sy, sz;

    PingParticle(float x, float y, float z, int life, Material *material, float sx, float sy, float sz);

    void particleLoop();
};

#endif // PARTICLE_H
