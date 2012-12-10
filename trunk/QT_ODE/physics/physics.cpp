#include "physics.h"

#include "scene/object.h"
#include "scene/scene.h"
#include "math/matrix4f.h"
#include "math/vector3f.h"
#include "math/quaternion4f.h"
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

                dJointID c = dJointCreateContact (scene->world,scene->contactGroup,&contact[i]);
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
    dJointGroupEmpty (scene->contactGroup);
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
    //    dWorldSetGravity (scene->world,0,-9.8,0);
    dWorldSetGravity (scene->world,0,0,0);
    dWorldSetERP (scene->world,0.2);
    //dWorldSetCFM (scene->world,1e-3);
    dWorldSetCFM (scene->world,1e-009);
    dCreatePlane (scene->space,0,1,0,0); //todo remove
    scene->contactGroup = dJointGroupCreate (0);

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

void Physics::createObject(Object *object, SpaceID space, float density, Vector3f position, Quaternion4f rotation){


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
        //            dMassSetBoxTotal(&object->mass,1000,object->properties[0],object->properties[1],object->properties[2]);
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

    float rot[] = {rotation.w,rotation.x,rotation.y,rotation.z};
    dBodySetQuaternion (object->body,rot);
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
    dJointGroupDestroy (scene->contactGroup);
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
void Physics::ControlPDBallDanilo(dJointID joint,dQuaternion tarQ,double ks,double kd)
{

    dBodyID parent = dJointGetBody(joint,0);
    dBodyID child = dJointGetBody(joint,1);

    const dReal* childQuaternion = dBodyGetQuaternion(child);
    const dReal* parentQuaternion = dBodyGetQuaternion(parent);
    const dReal* childAngularVelocity = dBodyGetAngularVel(child);
    const dReal* parentAngularVelocity = dBodyGetAngularVel(parent);


    dQuaternion tmp;  // Intermediate variable
    dQuaternion difQ; // Change to be applied to body 2 in global coords
    dQuaternion difGlobalQ;
    dVector3 relativeAngularVelocity;    // Relative angular velocity
    dVector3 distA;
    dVector3 torque = {0};

    dQuaternion ident = {1,0,0,0};

    dQMultiply1(tmp,childQuaternion,parentQuaternion);
    //    dQMultiply1(tmp,parentQuaternion,childQuaternion);

    float prodEsc = ident[0]*tmp[0] + ident[1]*tmp[1] + ident[2]*tmp[2] + ident[3]*tmp[3];
    if(prodEsc < 0){
        tmp[0]*=-1;
        tmp[1]*=-1;
        tmp[2]*=-1;
        tmp[3]*=-1;
    }

    dQMultiply0(difGlobalQ,tarQ,tmp);

    //dQMultiply0(difGlobalQ, parentQuaternion, difQ);

    dReal theta = 2*acos(difGlobalQ[0]);
    dReal s = 1-difGlobalQ[0]*difGlobalQ[0];
    s = 1/sqrt(s);

    // Ensure we're not going the long way around
    //if (theta>0) theta-=2*M_PI;
    distA[0] = difGlobalQ[1]*s;
    distA[1] = difGlobalQ[2]*s;
    distA[2] = difGlobalQ[3]*s;

    // Find the proportional component
    if (fabs(theta)>EPSILON) {
        dNormalize3(distA);

        dOPC(torque,*,distA,ks);
    }

    dVector3 vel;

    vel[0] = parentAngularVelocity[0] - childAngularVelocity[0];
    vel[1] = parentAngularVelocity[1] - childAngularVelocity[1];
    vel[2] = parentAngularVelocity[2] - childAngularVelocity[2];
    // Achando a velocidade entre as juntas
    dOP(relativeAngularVelocity,-,childAngularVelocity,parentAngularVelocity);
    // Aplicando o fator da constante de velocidade
    dOPEC(relativeAngularVelocity,*=,kd);
    // Adicoionando ao torque
    dOPE(torque,-=,relativeAngularVelocity);


    dBodyAddTorque(child,torque[0],torque[1],torque[2]);
    dBodyAddTorque(parent,-torque[0],-torque[1],-torque[2]);
}


void Physics::ControlPDBallRubens(Joint *joint,dQuaternion qTarget,double ks,double kd){
    dQuaternion qIdent = {1,0,0,0};

    dQuaternion qAux;
    const dReal *readQ;

    //prev
    readQ = dBodyGetQuaternion(joint->parent->body);
    dQuaternion qPrev = {readQ[0],readQ[1],readQ[2],readQ[3]};

    Quaternion4f *parentIniQ = joint->parent->initialRotation;
    dQuaternion prevIniQ = {parentIniQ->w, -parentIniQ->x, -parentIniQ->y, -parentIniQ->z};
    dQMultiply0 (qAux, qPrev, prevIniQ);

    qPrev[0] = qAux[0];
    qPrev[1] = -qAux[1];
    qPrev[2] = -qAux[2];
    qPrev[3] = -qAux[3];

    //next
    readQ = dBodyGetQuaternion(joint->child->body);
    dQuaternion qNext = {readQ[0],readQ[1],readQ[2],readQ[3]};

    Quaternion4f *childIniQ = joint->child->initialRotation;
    dQuaternion nextIniQ = {childIniQ->w, -childIniQ->x, -childIniQ->y, -childIniQ->z};
    dQMultiply0 (qAux, qNext, nextIniQ);

    qNext[0] = qAux[0];
    qNext[1] = qAux[1];
    qNext[2] = qAux[2];
    qNext[3] = qAux[3];

    //current quaternion
    dQuaternion qCurrent;
    dQMultiply0 (qCurrent, qPrev, qNext);

    dReal dotProdQ;

    //minor arc
    dotProdQ = ( qCurrent[0]*qIdent[0] + qCurrent[1]*qIdent[1] + qCurrent[2]*qIdent[2] + qCurrent[3]*qIdent[3] );
    if( dotProdQ < -dotProdQ ){
        qCurrent[0]*=-1;
        qCurrent[1]*=-1;
        qCurrent[2]*=-1;
        qCurrent[3]*=-1;
    }

    //dQuaternion qTarget = {1,0,0,0};

    dQuaternion qDelta;
    dQuaternion qMinusCurrent = {qCurrent[0],-qCurrent[1],-qCurrent[2],-qCurrent[3]};

    //delta quat
    dQMultiply0(qDelta, qTarget, qMinusCurrent);
    //minor arc
    dotProdQ = ( qDelta[0]*qIdent[0] + qDelta[1]*qIdent[1] + qDelta[2]*qIdent[2] + qDelta[3]*qIdent[3] );
    if( dotProdQ < -dotProdQ ){
        qDelta[0]*=-1;
        qDelta[1]*=-1;
        qDelta[2]*=-1;
        qDelta[3]*=-1;
    }

    //to axis angle
    dVector3 axis;
    dReal angle;

    angle = 2*acos(qDelta[0]);
    dReal s = qDelta[0]*qDelta[0];
    if(s > 0.0){
        s = dRecipSqrt(s);     //s = 1/sqrt(s)
        axis[0] = qDelta[1]*s; //x = qx*s
        axis[1] = qDelta[2]*s; //y = qy*s
        axis[2] = qDelta[3]*s; //z = qz*s
    }else{
        //arbitrary axis
        s = 0;
        axis[0] = 1;
        axis[1] = 1;
        axis[2] = 1;
    }

    //limited rad angle
    dReal limitedRadAngle = angle;
    dReal limT = 0.1*10;
    if(limitedRadAngle < -limT){
        limitedRadAngle = -limT;
    }else if(limitedRadAngle > limT){
        limitedRadAngle = limT;
    }

    //rad to deg
    angle = (angle*180)/M_PI;

    //truncate 10 decimal digits
    angle = trunc( angle * pow(10,10) ) / pow(10,10) ;
    axis[0] = trunc( axis[0] * pow(10,10) ) / pow(10,10) ;
    axis[1] = trunc( axis[1] * pow(10,10) ) / pow(10,10) ;
    axis[2] = trunc( axis[2] * pow(10,10) ) / pow(10,10) ;

    dVector3 localDelta = {axis[0]*limitedRadAngle, axis[1]*limitedRadAngle, axis[2]*limitedRadAngle, 1.0};

    const dReal *rotationPrevBody = dBodyGetRotation( dJointGetBody (joint->joint, 0) );

    dMatrix3 iniRot;
    dQuaternion iniQuat;

    "set iniQuat";

    dRfromQ(iniRot, iniQuat);

    dMatrix3 iniRotPrevBody;
    dMultiply2_333(iniRotPrevBody,rotationPrevBody,iniRot);

    dVector3 globalDelta;
    dMultiply0_331(globalDelta,iniRotPrevBody,localDelta);

    const dReal *prevBodyVel = dBodyGetAngularVel( dJointGetBody (joint->joint, 0) );
    const dReal *nextBodyVel = dBodyGetAngularVel( dJointGetBody (joint->joint, 1) );
    dVector3 globalVel;
    for(int i=0;i<3;i++){
        globalVel[i] = nextBodyVel[i] - prevBodyVel[i];
    }
    dVector3 deltaGlobalVel;
    limT = 0.1*1000;
    for(int i=0;i<3;i++){
        deltaGlobalVel[i] = -globalVel[i];

        if(deltaGlobalVel[i] < -limT){
            deltaGlobalVel[i] = -limT;
        }else if(deltaGlobalVel[i] > limT){
            deltaGlobalVel[i] = limT;
        }
    }

    //ks
    dMatrix3 localKS;
    for(int i=0;i<12;i++){ localKS[i] = 0; }

    dVector3 fixedKSI = {ks,ks,ks};// = getJointKsFixediSaved( i, state->compInertia, ksFixedi );

    localKS[0]  = fixedKSI[0];
    localKS[5]  = fixedKSI[1];
    localKS[10] = fixedKSI[2];

    dMatrix3 tempKS;
    dMultiply2_333 (tempKS,localKS,iniRotPrevBody);
    dMatrix3 globalKS;
    dMultiply0_333 (globalKS,iniRotPrevBody,tempKS);

    //kd

    //dReal ratioKSKD = 0.2;

    dMatrix3 localKD;
    for (int i=0;i<12;i++) { localKD[i] = 0.0; }
    localKD[0] = kd;
    localKD[5] = kd;
    localKD[10] = kd;
    //localKD[0]  = localKS[0] * ratioKSKD;
    //localKD[5]  = localKS[5] * ratioKSKD;
    //localKD[10] = localKS[10] * ratioKSKD;


    dMatrix3 tempKD;
    dMultiply2_333 (tempKD,localKD,iniRotPrevBody);
    dMatrix3 globalKD;
    dMultiply0_333 (globalKD,iniRotPrevBody,tempKD);

    dVector3 torque;
    dVector3 torqueKS;
    dMultiply0_331 (torqueKS,globalKS,globalDelta);
    dVector3 torqueKD;
    dMultiply0_331 (torqueKD,globalKD,deltaGlobalVel);

    for(int i=0;i<3;i++){
        torque[i] = torqueKS[i] + torqueKD[i];
    }

    dBodyAddTorque(joint->parent->body, -torque[0],-torque[1],-torque[2]);
    dBodyAddTorque(joint->child->body,  torque[0], torque[1], torque[2]);
}
