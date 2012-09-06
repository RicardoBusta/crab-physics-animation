//01234567890123456789012345678901234567890123456789012345678901234567890123456789
//0         1         2         3         4         5         6         7

//Program used to generate primitives without the need to recalculate points.

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define CLASS "GLPrimitive"
#define PI_180 0.017453292519943295769




void gen_sphere(int div);
void gen_box();
void gen_icosphere(int div);
void gen_icocapsule(int div);

ofstream out ("../graphics/glprimitive.cpp");

int main() {

    if (out.is_open()) {
        out << "//FILE GENERATED AUTOMATICALLY BY GENERATE_PRIMITIVE IN EXTRAS" << endl;

        out << "#include \"glprimitive.h\"" << endl;
        out << "#include <QtOpenGL>" << endl;

        out << endl;
        //gen_sphere(10);
        gen_icosphere(3);
        out << endl;
        gen_box();
        out << endl;
        gen_icocapsule(3);

        cout << "file generated with success!"<< endl;
    } else cout << "Unable to open file" << endl;

    return 0;
}

//--------------------------------------------------------------------------------
//SPHERE
//--------------------------------------------------------------------------------


void gen_sphere(int div) {
    out << "void " << CLASS << "::sphere(float r, float* rot){" << endl;
    out << "\t//SPHERE DIV " << div << endl;
    out << "\t//PARAM: r : ray" << endl;
    float angi = PI_180*360.0/div;
    float angj = PI_180*360.0/div;
    float ai1,ai2,aj1,aj2,x,y,z;

    for(int i=0; i<div/2; i++) {
        ai1 = angi*i+90;
        ai2 = angi*(i+1)+90;
        for(int j=0; j<div; j++) {
            aj1 = angj*j;
            aj2 = angj*(j+1);

            out << "\tglBegin(GL_QUADS);" << endl;
            x = cos(ai1)*cos(aj1);
            y = sin(ai1);
            z = cos(ai1)*sin(aj1);
            out << "\tglNormal3f("<<x<<","<<y<<","<<z<<");" << endl;
            out << "\tglVertex3f(r*"<<x<<",r*"<<y<<",r*"<<z<<");" << endl;
            x = cos(ai1)*cos(aj2);
            z = cos(ai1)*sin(aj2);
            out << "\tglNormal3f("<<x<<","<<y<<","<<z<<");" << endl;
            out << "\tglVertex3f(r*"<<x<<",r*"<<y<<",r*"<<z<<");" << endl;
            x = cos(ai2)*cos(aj2);
            y = sin(ai2);
            z = cos(ai2)*sin(aj2);
            out << "\tglNormal3f("<<x<<","<<y<<","<<z<<");" << endl;
            out << "\tglVertex3f(r*"<<x<<",r*"<<y<<",r*"<<z<<");" << endl;
            x = cos(ai2)*cos(aj1);
            z = cos(ai2)*sin(aj1);
            out << "\tglNormal3f("<<x<<","<<y<<","<<z<<");" << endl;
            out << "\tglVertex3f(r*"<<x<<",r*"<<y<<",r*"<<z<<");" << endl;
            out << "\tglEnd();" << endl;

        }
    }

    out << "}" << endl;
}

//--------------------------------------------------------------------------------
//BOX
//--------------------------------------------------------------------------------

void gen_box() {
    out << "void " << CLASS << "::box(float lx, float ly, float lz, float* rot){" << endl;
    out << "\t//BOX" << endl;
    out << "\t//PARAM: lx : x length / ly : y length / lz : z length" << endl;
    out << "\tglBegin(GL_QUADS);" << endl;
    //front
    out << "\tglNormal3f(0,0,+1);" << endl;
    out << "\tglVertex3f(-lx,-ly,+lz);" << endl;
    out << "\tglVertex3f(+lx,-ly,+lz);" << endl;
    out << "\tglVertex3f(+lx,+ly,+lz);" << endl;
    out << "\tglVertex3f(-lx,+ly,+lz);" << endl;
    //back
    out << "\tglNormal3f(0,0,-1);" << endl;
    out << "\tglVertex3f(-lx,-ly,-lz);" << endl;
    out << "\tglVertex3f(-lx,+ly,-lz);" << endl;
    out << "\tglVertex3f(+lx,+ly,-lz);" << endl;
    out << "\tglVertex3f(+lx,-ly,-lz);" << endl;
    //left
    out << "\tglNormal3f(-1,0,0);" << endl;
    out << "\tglVertex3f(-lx,-ly,-lz);" << endl;
    out << "\tglVertex3f(-lx,-ly,+lz);" << endl;
    out << "\tglVertex3f(-lx,+ly,+lz);" << endl;
    out << "\tglVertex3f(-lx,+ly,-lz);" << endl;
    //right
    out << "\tglNormal3f(+1,0,0);" << endl;
    out << "\tglVertex3f(+lx,-ly,-lz);" << endl;
    out << "\tglVertex3f(+lx,+ly,-lz);" << endl;
    out << "\tglVertex3f(+lx,+ly,+lz);" << endl;
    out << "\tglVertex3f(+lx,-ly,+lz);" << endl;
    //top
    out << "\tglNormal3f(0,+1,0);" << endl;
    out << "\tglVertex3f(-lx,+ly,-lz);" << endl;
    out << "\tglVertex3f(-lx,+ly,+lz);" << endl;
    out << "\tglVertex3f(+lx,+ly,+lz);" << endl;
    out << "\tglVertex3f(+lx,+ly,-lz);" << endl;
    //bottom
    out << "\tglNormal3f(0,-1,0);" << endl;
    out << "\tglVertex3f(-lx,-ly,-lz);" << endl;
    out << "\tglVertex3f(+lx,-ly,-lz);" << endl;
    out << "\tglVertex3f(+lx,-ly,+lz);" << endl;
    out << "\tglVertex3f(-lx,-ly,+lz);" << endl;
    out << "\tglEnd();" << endl;
    out << "}" << endl;
}

//--------------------------------------------------------------------------------
//ICOSPHERE
//--------------------------------------------------------------------------------

void icosphere_rec(float x1, float y1, float z1,
                   float x2, float y2, float z2,
                   float x3, float y3, float z3,
                   int depth) {

    float x123 = (x1+x2+x3);
    float y123 = (y1+y2+y3);
    float z123 = (z1+z2+z3);

    float d = sqrt( (x123*x123) + (y123*y123) + (z123*z123) );
    x123/=d;
    y123/=d;
    z123/=d;

    if(depth>0) {
        float x12 = (x1+x2);
        float y12 = (y1+y2);
        float z12 = (z1+z2);
        d = sqrt( (x12*x12) + (y12*y12) + (z12*z12) );
        x12/=d;
        y12/=d;
        z12/=d;

        float x23 = (x2+x3);
        float y23 = (y2+y3);
        float z23 = (z2+z3);
        d = sqrt( (x23*x23) + (y23*y23) + (z23*z23) );
        x23/=d;
        y23/=d;
        z23/=d;

        float x31 = (x3+x1);
        float y31 = (y3+y1);
        float z31 = (z3+z1);
        d = sqrt( (x31*x31) + (y31*y31) + (z31*z31) );
        x31/=d;
        y31/=d;
        z31/=d;

        icosphere_rec(x12,y12,z12, x23,y23,z23, x31,y31,z31 ,depth-1);
        icosphere_rec(x1,y1,z1, x12,y12,z12, x31,y31,z31 ,depth-1);
        icosphere_rec(x2,y2,z2, x23,y23,z23, x12,y12,z12 ,depth-1);
        icosphere_rec(x3,y3,z3, x31,y31,z31, x23,y23,z23 ,depth-1);
    } else {
        out << "\tglNormal3f("<<x1<<","<<y1<<","<<z1<<");" << endl;
        //out << "\tglNormal3f("<<x123<<","<<y123<<","<<z123<<");" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<",r*"<<z1<<");" << endl;
        out << "\tglNormal3f("<<x2<<","<<y2<<","<<z2<<");" << endl;
        //out << "\tglNormal3f("<<x123<<","<<y123<<","<<z123<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<",r*"<<z2<<");" << endl;
        out << "\tglNormal3f("<<x3<<","<<y3<<","<<z3<<");" << endl;
        //out << "\tglNormal3f("<<x123<<","<<y123<<","<<z123<<");" << endl;
        out << "\tglVertex3f(r*"<<x3<<",r*"<<y3<<",r*"<<z3<<");" << endl;
    }
}

void gen_icosphere(int div) {
    out << "void " << CLASS << "::sphere(float r, float* rot){" << endl;
    out << "\t//SPHERE DIV " << div << endl;
    out << "\t//PARAM: r : ray" << endl;

    out << "\tglBegin(GL_TRIANGLES);" << endl;
    icosphere_rec(0,1,0, 0,0,1, 1,0,0 ,div);
    icosphere_rec(0,1,0, 1,0,0, 0,0,-1 ,div);
    icosphere_rec(0,1,0, 0,0,-1, -1,0,0 ,div);
    icosphere_rec(0,1,0, -1,0,0, 0,0,1 ,div);

    icosphere_rec(0,-1,0, 1,0,0, 0,0,1 ,div);
    icosphere_rec(0,-1,0, 0,0,-1, 1,0,0 ,div);
    icosphere_rec(0,-1,0, -1,0,0, 0,0,-1 ,div);
    icosphere_rec(0,-1,0, 0,0,1, -1,0,0 ,div);
    out << "\tglEnd();" << endl;

    out << "}" << endl;
}

//--------------------------------------------------------------------------------
//ICOCAPSULE
//--------------------------------------------------------------------------------

void icocapsule_pole_rec(float x1, float y1, float z1,
                         float x2, float y2, float z2,
                         float x3, float y3, float z3,
                         bool top, int depth) {

    float x123 = (x1+x2+x3);
    float y123 = (y1+y2+y3);
    float z123 = (z1+z2+z3);

    float d = sqrt( (x123*x123) + (y123*y123) + (z123*z123) );
    x123/=d;
    y123/=d;
    z123/=d;

    if(depth>0) {
        float x12 = (x1+x2);
        float y12 = (y1+y2);
        float z12 = (z1+z2);
        d = sqrt( (x12*x12) + (y12*y12) + (z12*z12) );
        x12/=d;
        y12/=d;
        z12/=d;

        float x23 = (x2+x3);
        float y23 = (y2+y3);
        float z23 = (z2+z3);
        d = sqrt( (x23*x23) + (y23*y23) + (z23*z23) );
        x23/=d;
        y23/=d;
        z23/=d;

        float x31 = (x3+x1);
        float y31 = (y3+y1);
        float z31 = (z3+z1);
        d = sqrt( (x31*x31) + (y31*y31) + (z31*z31) );
        x31/=d;
        y31/=d;
        z31/=d;

        icocapsule_pole_rec(x12,y12,z12, x23,y23,z23, x31,y31,z31 ,top,depth-1);
        icocapsule_pole_rec(x1,y1,z1, x12,y12,z12, x31,y31,z31 ,top,depth-1);
        icocapsule_pole_rec(x2,y2,z2, x23,y23,z23, x12,y12,z12 ,top,depth-1);
        icocapsule_pole_rec(x3,y3,z3, x31,y31,z31, x23,y23,z23 ,top,depth-1);
    } else {
        char offset;
        if(top)
            offset = '+';
        else
            offset = '-';
        out << "\tglNormal3f("<<x1<<","<<y1<<","<<z1<<");" << endl;
        //out << "\tglNormal3f("<<x123<<","<<y123<<","<<z123<<");" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<offset<<"l,r*"<<z1<<");" << endl;
        out << "\tglNormal3f("<<x2<<","<<y2<<","<<z2<<");" << endl;
        //out << "\tglNormal3f("<<x123<<","<<y123<<","<<z123<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<offset<<"l,r*"<<z2<<");" << endl;
        out << "\tglNormal3f("<<x3<<","<<y3<<","<<z3<<");" << endl;
        //out << "\tglNormal3f("<<x123<<","<<y123<<","<<z123<<");" << endl;
        out << "\tglVertex3f(r*"<<x3<<",r*"<<y3<<offset<<"l,r*"<<z3<<");" << endl;
    }
}

void icocapsule_center_rec(float x1, float y1, float z1,
                           float x2, float y2, float z2,
                           float x3, float y3, float z3,
                           float x4, float y4, float z4,
                           int depth ) {
    if(depth>0) {
    } else {
    }
}

void gen_icocapsule(int div) {
    out << "void " << CLASS << "::capsule(float r, float l, float* rot){" << endl;
    out << "\t//SPHERE DIV " << div << endl;
    out << "\t//PARAM: r : ray" << endl;

    out << "\tglBegin(GL_TRIANGLES);" << endl;
    icocapsule_pole_rec(0,1,0, 0,0,1, 1,0,0 ,true,div);
    icocapsule_pole_rec(0,1,0, 1,0,0, 0,0,-1 ,true,div);
    icocapsule_pole_rec(0,1,0, 0,0,-1, -1,0,0 ,true,div);
    icocapsule_pole_rec(0,1,0, -1,0,0, 0,0,1 ,true,div);

    icocapsule_pole_rec(0,-1,0, 1,0,0, 0,0,1 ,false,div);
    icocapsule_pole_rec(0,-1,0, 0,0,-1, 1,0,0 ,false,div);
    icocapsule_pole_rec(0,-1,0, -1,0,0, 0,0,-1 ,false,div);
    icocapsule_pole_rec(0,-1,0, 0,0,1, -1,0,0 ,false,div);

	icocapsule_center_rec(1,0,0, 0,0,-1, -1,0,0, 0,0,1, )
    out << "\tglEnd();" << endl;

    out << "}" << endl;
}


//--------------------------------------------------------------------------------
//SHAPE
//--------------------------------------------------------------------------------

void gen_shape() {
}
