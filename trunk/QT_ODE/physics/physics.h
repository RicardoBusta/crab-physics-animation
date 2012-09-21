#ifndef PHYSICS_H
#define PHYSICS_H

#include <ode/ode.h>

#define BodyID dBodyID
#define GeomID dGeomID
#define WorldID dWorldID

namespace Physics{
    // The dynamic world properties.
    static dWorldID world;
    static dSpaceID space;
    static dBodyID body;
    static dGeomID geom;
    static dMass m;
    // Joint group for contact. Created and cleared on every step.
    static dJointGroupID contactGroup;

    void nearCallback(void *data, dGeomID o1, dGeomID o2);
    //void simLoop(int pause);

    void worldStep(WorldID world, float stepSize);

    void init();
    void close();
}

#endif // PHYSICS_H
