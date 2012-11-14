#include "physics.h"

#include "scene/object.h"
#include "scene/scene.h"
#include "math/matrix4f.h"
#include "math/vector3f.h"
#include "scene/character.h"
#include "scene/joint.h"

#ifdef DEBUG_MODE
#include <iostream>
using namespace std;
#endif

void Physics::nearCallback(void *data, dGeomID o1, dGeomID o2){
    if (dGeomIsSpace (o1) || dGeomIsSpace (o2)) {
        // Collide a space with everything else
        dSpaceCollide2 (o1, o2, data,&nearCallback);

    }else{
        Scene *scene = ((Object*)dGeomGetData(o1))->scene;

        dBodyID b1 = dGeomGetBody(o1);
        dBodyID b2 = dGeomGetBody(o2);

        int numcont = 2;
        dContact contact[numcont];

        if (int numc = dCollide (o1,o2,numcont,&contact[0].geom,sizeof(dContact))) {
            for(int i=0;i<numc;i++){

                contact[i].surface.mode = dContactBounce; // | dContactSoftCFM;
                // friction parameter
                contact[i].surface.mu = dInfinity;
                // bounce is the amount of "bouncyness".
                contact[i].surface.bounce = 0.1;
                // bounce_vel is the minimum incoming velocity to cause a bounce
                contact[i].surface.bounce_vel = 0.0;
                // constraint force mixing parameter
                //contact.surface.soft_cfm = 0.001;

                dJointID c = dJointCreateContact (scene->world,Physics::contactGroup,&contact[i]);
                dJointAttach (c,b1,b2);
            }
        }
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
    dWorldQuickStep (scene->world,0.001);
    // remove all contact joints
    dJointGroupEmpty (Physics::contactGroup);
}

void Physics::initCharacter(Character *chara){
    chara->space = dHashSpaceCreate (chara->scene->space);
    chara->jointGroup = dJointGroupCreate(0);
}

void Physics::closeCharacter(Character *chara){
    dJointGroupDestroy(chara->jointGroup);
    dSpaceDestroy(chara->space);
}

void Physics::initScene(Scene *scene){
    //!This might have to change place when many scenes are initing...
    dInitODE ();
    // create world
    scene->world = dWorldCreate ();
    scene->space = dHashSpaceCreate (0);
    dWorldSetGravity (scene->world,0,-9.8,0);
    //dWorldSetGravity (scene->world,0,0,0);
    dWorldSetERP (scene->world,0.2);
    //dWorldSetCFM (scene->world,1e-3);
    dWorldSetCFM (scene->world,1e-009);
    dCreatePlane (scene->space,0,1,0,0); //todo remove
    Physics::contactGroup = dJointGroupCreate (0);

    //juntas ligadas - >ERP:+ligadas
    //dWorldSetCFM (world,1e-009); //soft hard (colisao)- >CFM:+soft
    dWorldSetAutoDisableFlag (scene->world,1);
    dWorldSetContactMaxCorrectingVel (scene->world,0.3);
    dWorldSetContactSurfaceLayer (scene->world,0.00001);
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

void Physics::createObject(Object *object, SpaceID space, float density, Vector3f position, Vector3f rotation){


    switch(object->shape){
        case OBJ_SPHERE:
            object->body = dBodyCreate (object->scene->world);
            object->geometry = dCreateSphere (space,object->properties[0]);
            dMassSetSphere (&object->mass,density,object->properties[0]);
            break;
        case OBJ_BOX:
            object->body = dBodyCreate (object->scene->world);
            object->geometry = dCreateBox (space,object->properties[0],object->properties[1],object->properties[2]);
            dMassSetBox (&object->mass,density,object->properties[0],object->properties[1],object->properties[2]);
            break;
        case OBJ_CAPSULE:
            object->body = dBodyCreate (object->scene->world);
            object->geometry = dCreateCapsule (space,object->properties[0],object->properties[1]);
            dMassSetCapsule (&object->mass,density,1,object->properties[0],object->properties[1]);
            break;
        case OBJ_CYLINDER:
            object->body = dBodyCreate (object->scene->world);
            object->geometry = dCreateCylinder (space,object->properties[0],object->properties[1]);
            dMassSetCylinder (&object->mass,density,1,object->properties[0],object->properties[1]);
            break;
        default:
            return;
            break;
    }

    dGeomSetData(object->geometry, (void*)(object));
    dBodySetMass (object->body,&object->mass);
    dGeomSetBody (object->geometry,object->body);
    dBodySetPosition (object->body,position.getX(),position.getY(),position.getZ());
    //dBodySetRotation (object->body,tr);
}

Vector3f Physics::getObjectPosition(Object *obj){
    Vector3f res;

    const dReal *pos;
    pos = dGeomGetPosition(obj->geometry);

    res.setX(pos[0]);
    res.setY(pos[1]);
    res.setZ(pos[2]);

    return res;
}

void Physics::closeScene(Scene *scene){
    // clean up
    dJointGroupDestroy (Physics::contactGroup);
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

    /*
    0 4 8
    1 5 9
    2 6 10
    3 7 11
    */

    //TODO FIX THIS
    /*
    int j[] = {+1,-1,+1,+1,
               -1,+1,-1,+1,
               +1,-1,+1,+1};
               */


    transform->set( 0, rot[0] );
    //    matrix[0]=R[0];
    transform->set( 1, rot[4] );
    //    matrix[1]=R[4];
    transform->set( 2, rot[8] );
    //    matrix[2]=R[8];
    transform->set( 3, 0 );
    //    matrix[3]=0;
    transform->set( 4, rot[1] );
    //    matrix[4]=R[1];
    transform->set( 5, rot[5] );
    //    matrix[5]=R[5];
    transform->set( 6, rot[9] );
    //    matrix[6]=R[9];
    transform->set( 7, 0 );
    //    matrix[7]=0;
    transform->set( 8, rot[2] );
    //    matrix[8]=R[2];
    transform->set( 9, rot[6] );
    //    matrix[9]=R[6];
    transform->set( 10, rot[10] );
    //    matrix[10]=R[10];
    transform->set( 11, 0 );
    //    matrix[11]=0;

    /*
    for(int i=0;i<12;i++){
        if(i!=1 and i!=4 and i!=6 and i!=9){
            transform->set( i, rot[i] );
        }else{
            transform->set( i, -rot[i] );
        }
    }*/

    transform->set( 12, 0.0 );
    transform->set( 13, 0.0 );
    transform->set( 14, 0.0 );
    transform->set( 15, 1.0 );

    transform->translate(pos[0],pos[1],pos[2]);
}

void Physics::initJointBall(Joint* joint, Vector3f anchor){
    joint->joint = dJointCreateBall(joint->character->scene->world, joint->character->jointGroup);
    dJointAttach(joint->joint, joint->parent->body, joint->child->body);
    dJointSetBallAnchor(joint->joint, anchor.getX(), anchor.getY(), anchor.getZ());
    //dJointSetBallAnchor2(joint->joint, anchor.getX(), anchor.getY(), anchor.getZ());
}

Vector3f Physics::getJointBallAnchor( Joint* joint ){
    Vector3f result;

    dVector3 res;

    dJointGetBallAnchor( joint->joint, res );

    float r = res[0];
    result.setX( r );
    result.setY( (float)res[1] );
    result.setZ( (float)res[2] );

    return result;
}

void Physics::closeJoint(Joint* joint){
    dJointDestroy(joint->joint);
}

void Physics::bodyAddTorque(dBodyID body, dReal x, dReal y, dReal z){
    dBodyAddTorque(body,x,y,z);
}

void Physics::bodySetTorque(dBodyID body, dReal x, dReal y, dReal z){
    dBodySetTorque(body,x,y,z);
}

void Physics::bodyAddForce(dBodyID body, dReal x, dReal y, dReal z){
    dBodyAddForce(body,x,y,z);
}

void Physics::bodySetForce(dBodyID body, dReal x, dReal y, dReal z){
    dBodySetForce(body,x,y,z);
}


#define EPSILON 0.01
void Physics::ControlPDBall(dJointID joint,dQuaternion tarQ,double ks,double kd)
{

    dBodyID father = dJointGetBody(joint,0);
    dBodyID son = dJointGetBody(joint,1);

    const dReal* q1 = dBodyGetQuaternion(son);
    const dReal* q2 = dBodyGetQuaternion(father);
    const dReal* a1 = dBodyGetAngularVel(son);
    const dReal* a2 = dBodyGetAngularVel(father);


    dQuaternion tmp;  // Intermediate variable
    dQuaternion difQ; // Change to be applied to body 2 in global coords
    dVector3 difA;    // Relative angular velocity
    dVector3 distA;
    dVector3 torque = {0};

    dQMultiply1(tmp,q1,q2);
    dQMultiply0(difQ,tarQ,tmp);

    dReal theta = 2*acos(difQ[0]);
    dReal s = 1-difQ[0]*difQ[0];
    s = 1/sqrt(s);
    // Ensure we're not going the long way around
    if (theta>M_PI) theta-=2*M_PI;
    distA[0] = difQ[1]*s;
    distA[1] = difQ[2]*s;
    distA[2] = difQ[3]*s;

    // Find the proportional component
    if (fabs(theta)>EPSILON) {
        dNormalize3(distA);

        dOPC(torque,*,distA,ks);
    }



    dVector3 vel;


    vel[0] = a2[0] - a1[0];
    vel[1] = a2[1] - a1[1];
    vel[2] = a2[2] - a1[2];
    // Achando a velocidade entre as juntas
    dOP(difA,-,a1,a2);
    // Aplicando o fator da constante de velocidade
    dOPEC(difA,*=,kd);
    // Adicoionando ao torque
    dOPE(torque,-=,difA);


    dBodyAddTorque(son,torque[0],torque[1],torque[2]);
    dBodyAddTorque(father,-torque[0],-torque[1],-torque[2]);
}
