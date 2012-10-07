#include "physics.h"

#include "scene/object.h"
#include "scene/scene.h"
#include "math/matrix4f.h"

void Physics::nearCallback(void *data, dGeomID o1, dGeomID o2){
    Scene *scene = ((Object*)dGeomGetData(o1))->scene;

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
    if (/*int numc =*/ dCollide (o1,o2,1,&contact.geom,sizeof(dContact))) {
        dJointID c = dJointCreateContact (scene->world,contactGroup,&contact);
        dJointAttach (c,b1,b2);
    }
}

void Physics::worldStep(WorldID world, float stepSize){
    dWorldQuickStep(world, stepSize);
}

void Physics::simSingleStep (Scene *scene)
{
    // find collisions and add contact joints
    dSpaceCollide (scene->space,0,&nearCallback);
    // step the simulation
    dWorldQuickStep (scene->world,0.01);
    // remove all contact joints
    dJointGroupEmpty (contactGroup);
}

void Physics::init(Scene *scene){
    //!This might have to change place when many scenes are initing...
    dInitODE ();
    // create world
    scene->world = dWorldCreate ();
    scene->space = dHashSpaceCreate (0);
    dWorldSetGravity (scene->world,0,-0.2,0);
    dWorldSetCFM (scene->world,1e-5);
    dCreatePlane (scene->space,0,1,0,0);
    contactGroup = dJointGroupCreate (0);
    // create object
    //    body = dBodyCreate (world);
    //    geom = dCreateSphere (space,0.5);
    //    dMassSetSphere (&m,1,0.5);
    //    dBodySetMass (body,&m);
    //    dGeomSetBody (geom,body);
    // set initial position
    //    dBodySetPosition (body,0,0,3);
    // run simulation
}

void Physics::createObject(Object *object, dReal posx, dReal posy, dReal posz){


    switch(object->shape){
    case OBJ_SPHERE:
        object->body = dBodyCreate (object->scene->world);
        object->geometry = dCreateSphere (object->scene->space,object->properties[0]);
        dGeomSetData(object->geometry, (void*)(object));
        dMassSetSphere (&object->mass,1,object->properties[0]);
        dBodySetMass (object->body,&object->mass);
        dGeomSetBody (object->geometry,object->body);
        dBodySetPosition (object->body,posx,posy,posz);
        break;
    case OBJ_BOX:
        object->body = dBodyCreate (object->scene->world);
        object->geometry = dCreateBox (object->scene->space,object->properties[0],object->properties[1],object->properties[2]);
        dGeomSetData(object->geometry, (void*)(object));
        dMassSetBox (&object->mass,1,object->properties[0],object->properties[1],object->properties[2]);
        dBodySetMass (object->body,&object->mass);
        dGeomSetBody (object->geometry,object->body);
        dBodySetPosition (object->body,posx,posy,posz);
        break;
    default:
        break;
    }
}

void Physics::close(Scene *scene){
    // clean up
    dJointGroupDestroy (contactGroup);
    dSpaceDestroy (scene->space);
    dWorldDestroy (scene->world);
    //!Same with close
    dCloseODE();
}

void Physics::getGeomTransform(GeomID geom, Matrix4f *transform){

    const dReal *pos;
    const dReal *rot;
    pos = dGeomGetPosition (geom);
    rot = dGeomGetRotation (geom);

    for(int i=0;i<12;i++){
        transform->set( i,rot[i] );
    }
    transform->set( 12, 0.0 );
    transform->set( 13, 0.0 );
    transform->set( 14, 0.0 );
    transform->set( 15, 1.0 );

    transform->translate(pos[0],pos[1],pos[2]);
}
