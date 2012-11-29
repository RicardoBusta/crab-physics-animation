#ifndef PHYSICS_H
#define PHYSICS_H

#include <ode/ode.h>

#define BodyID dBodyID
#define GeomID dGeomID
#define WorldID dWorldID
#define SpaceID dSpaceID
#define Mass dMass
#define JointID dJointID
#define JointGroupID dJointGroupID

class Matrix4f;
class Vector3f;
class Quaternion4f;
class Scene;
class Object;
class Character;
class Joint;

namespace Physics{
    // The dynamic world properties.
    //static dWorldID world;
    //static dSpaceID space;
    //static dBodyID body;
    //static dGeomID geom;
    //static dMass m;
    // Joint group for contact. Created and cleared on every step.
    //static dJointGroupID contactGroup;

    void nearCallback(void *data, dGeomID o1, dGeomID o2);
    void simSingleStep(Scene *scene);
    void worldStep(WorldID world, float stepSize);
    void getGeomTransform(GeomID geom, Matrix4f* transform);
    void createObject(Object *obj, dSpaceID space, float density, Vector3f position, Quaternion4f rotation);

    //Body Manipulation
    Vector3f getObjectPosition(Object *obj);

    void bodySetTorque(BodyID body, dReal x, dReal y, dReal z);
    void bodyAddTorque(BodyID body, dReal x, dReal y, dReal z);

    void bodySetForce(BodyID body, dReal x, dReal y, dReal z);
    void bodyAddForce(BodyID body, dReal x, dReal y, dReal z);

    void initJointBall(Joint* joint, Vector3f anchor);
    Vector3f getJointBallAnchor( Joint* joint );
    void closeJoint(Joint* joint);

    //
    void initCharacter(Character *chara);
    void closeCharacter(Character *chara);

    //Must use
    void initScene(Scene *scene);
    void closeScene(Scene *scene);

    //PD Controllers

    void ControlPDBall(dJointID joint,dQuaternion tarQ,double ks,double kd);
}

#endif // PHYSICS_H
