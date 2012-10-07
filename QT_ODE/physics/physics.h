#ifndef PHYSICS_H
#define PHYSICS_H

#include <ode/ode.h>

#define BodyID dBodyID
#define GeomID dGeomID
#define WorldID dWorldID
#define SpaceID dSpaceID
#define Mass dMass

class Matrix4f;
class Scene;
class Object;

namespace Physics{
    // The dynamic world properties.
    //static dWorldID world;
    //static dSpaceID space;
    //static dBodyID body;
    //static dGeomID geom;
    //static dMass m;
    // Joint group for contact. Created and cleared on every step.
    static dJointGroupID contactGroup;

    void nearCallback(void *data, dGeomID o1, dGeomID o2);
    void simSingleStep(Scene *scene);

    void worldStep(WorldID world, float stepSize);

    void getGeomTransform(GeomID geom, Matrix4f* transform);

    void createObject(Object *obj, dReal posx, dReal posy, dReal posz);

    void init(Scene *scene);
    void close(Scene *scene);
}

#endif // PHYSICS_H
