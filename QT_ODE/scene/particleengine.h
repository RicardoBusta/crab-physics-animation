#ifndef PARTICLEENGINE_H
#define PARTICLEENGINE_H

class Scene;
class Material;

class ParticleEngine
{
public:
    float x, y, z;

    int timeout;
    int life;

    Scene *scene;

    Material *material;

    ParticleEngine(float x, float y, float z, int timeout, Scene *scene);
    virtual ~ParticleEngine();

    virtual void tick()=0;
};

class PESignal:public ParticleEngine
{
public:
    PESignal(float x, float y, float z, int timeout, Scene *scene)
        :ParticleEngine(x,y,z,timeout,scene){}

    void tick();
};

#endif // PARTICLEENGINE_H
