#include "physics.h"

void Physics::nearCallback(void *data, dGeomID o1, dGeomID o2){
    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);
    dContact contact;
    contact.surface.mode = dContactBounce | dContactSoftCFM;
    // friction parameter
    contact.surface.mu = dInfinity;
    // bounce is the amount of "bouncyness".
    contact.surface.bounce = 0.9;
    // bounce_vel is the minimum incoming velocity to cause a bounce
    contact.surface.bounce_vel = 0.1;
    // constraint force mixing parameter
    contact.surface.soft_cfm = 0.001;
    if (int numc = dCollide (o1,o2,1,&contact.geom,sizeof(dContact))) {
        dJointID c = dJointCreateContact (world,contactGroup,&contact);
        dJointAttach (c,b1,b2);
    }
}

void Physics::worldStep(WorldID world, float stepSize){
    dWorldQuickStep(world, stepSize);
}

/*
void Physics::simLoop (int pause)
{
    const dReal *pos;
    const dReal *R;
    // find collisions and add contact joints
    dSpaceCollide (space,0,&nearCallback);
    // step the simulation
    dWorldQuickStep (world,0.01);
    // remove all contact joints
    dJointGroupEmpty (contactGroup);
    // redraw sphere at new location
    pos = dGeomGetPosition (geom);
    R = dGeomGetRotation (geom);
    //dsDrawSphere (pos,R,dGeomSphereGetRadius (geom));
}*/

void Physics::init(){
    dInitODE ();
    // create world
    world = dWorldCreate ();
    space = dHashSpaceCreate (0);
    dWorldSetGravity (world,0,0,-0.2);
    dWorldSetCFM (world,1e-5);
    dCreatePlane (space,0,0,1,0);
    contactGroup = dJointGroupCreate (0);
    // create object
    body = dBodyCreate (world);
    geom = dCreateSphere (space,0.5);
    dMassSetSphere (&m,1,0.5);
    dBodySetMass (body,&m);
    dGeomSetBody (geom,body);
    // set initial position
    dBodySetPosition (body,0,0,3);
    // run simulation
}

void Physics::close(){
    // clean up
    dJointGroupDestroy (contactGroup);
    dSpaceDestroy (space);
    dWorldDestroy (world);
    dCloseODE();
}
