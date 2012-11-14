//01234567890123456789012345678901234567890123456789012345678901234567890123456789
//0         1         2         3         4         5         6         7

//Program used to generate primitives without the need to recalculate points.

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define CLASS "GLPrimitive"
#define PI_180 0.017453292519943295769

#define INVERSE_GROWTH 1.3

void gen_sphere(int div);
void gen_box();
void gen_box_wire();
void gen_icosphere(int div);
void gen_icosphere_wire(int div);
void gen_icocapsule(int div);
void gen_icocapsule_wire(int div);
void gen_icocylinder(int div);
void gen_icocylinder_wire(int div);
void gen_chess_plane(int div);
void gen_chess_floor();
void gen_circle();
void gen_vector();

ofstream out ("../graphics/glprimitive.cpp");

void transform_code_begin() {
    out << "\tglPushMatrix(); " << endl;
    out << "\tfloat transform[16]; " << endl;
    out << "\tt->get(transform); " << endl;
    out << "\tglMultMatrixf(transform); " << endl;
}
void transform_code_end() {
    out << "\tglPopMatrix(); " << endl;
}
void material_code(bool inverse=false, bool half = false){
    out << endl << "if(mat!=NULL){" << endl;
    if(half){
        out << endl << "\tmat->glHalf();" << endl;
    }else if(inverse){
        out << endl << "\tmat->glInverse();" << endl;
    }else{
        out << endl << "\tmat->gl();" << endl;
    }
    out << endl << "}" << endl;
}

int main() {

    if (out.is_open()) {
        out << "//FILE GENERATED AUTOMATICALLY BY GENERATE_PRIMITIVE IN EXTRAS" << endl;

        out << "#include \"glprimitive.h\"" << endl;
        out << endl << "#include <QtOpenGL>" << endl;
        out << endl << "#include \"graphics/material.h\"" << endl;
        out << endl << "#include \"math/matrix4f.h\"" << endl;
        out << endl << "#include \"math/vector3f.h\"" << endl;
        out << endl;

        // SPHERE
        out << "void " << CLASS << "::sphere(float r, Material *mat, Matrix4f *t){" << endl;
        transform_code_begin();
        //gen_sphere(10);
        gen_icosphere(2);
        transform_code_end();
        out << "}" << endl << endl;

        // WIRE SPHERE
        out << "void " << CLASS << "::wire_sphere(float r, Material *mat, Matrix4f *t){" << endl;
        transform_code_begin();
        //gen_sphere(10);
        gen_icosphere_wire(2);
        transform_code_end();
        out << "}" << endl << endl;

        // BOX
        out << "void " << CLASS << "::box(float lx, float ly, float lz, Material *mat, Matrix4f *t){" << endl;
        transform_code_begin();
        gen_box();
        transform_code_end();
        out << "}" << endl << endl;

        // WIRE BOX
        out << "void " << CLASS << "::wire_box(float lx, float ly, float lz, Material *mat, Matrix4f *t){" << endl;
        transform_code_begin();
        gen_box_wire();
        transform_code_end();
        out << "}" << endl << endl;

        // CAPSULE
        out << "void " << CLASS << "::capsule(float r, float l, Material *mat, Matrix4f *t){" << endl;
        transform_code_begin();
        out << "glRotatef(90,1,0,0);" << endl;
        gen_icocapsule(1);
        transform_code_end();
        out << "}" << endl << endl;

        // CYLINDER
        out << "void " << CLASS << "::cylinder(float r, float l, Material *mat, Matrix4f *t){" << endl;
        transform_code_begin();
        out << "glRotatef(90,1,0,0);" << endl;
        gen_icocylinder(1);
        transform_code_end();
        out << "}" << endl << endl;

        // PLANE
        out << "void " << CLASS << "::plane(float s, Material *mat, Matrix4f *t){" << endl;
        transform_code_begin();
        gen_chess_plane(10);
        transform_code_end();
        out << "}" << endl << endl;

        // FLOOR
        out << "void " << CLASS << "::floor(float s, Material *mat){" << endl;
        //transform_code_begin();
        gen_chess_floor();
        //transform_code_end();
        out << "}" << endl << endl;

        // CIRCLE
        out << "void " << CLASS << "::circle(float r, Material *mat, Matrix4f *t){" << endl;
        transform_code_begin();
        gen_circle();
        transform_code_end();
        out << "}" << endl << endl;

        // VECTOR
        out << "void " << CLASS << "::vector( Vector3f vector, Vector3f pos, Material *mat){" << endl;
        //transform_code_begin();
        gen_vector();
        //transform_code_end();
        out << "}" << endl << endl;

        // BB CIRCLE
        out << "void " << CLASS << "::bb_circle(float r, Material *mat){" << endl;
        //transform_code_begin();
        gen_circle();
        //transform_code_end();
        out << "}" << endl << endl;

                // CYLINDER
        out << "void " << CLASS << "::wire_cylinder(float r, float l, Material *mat, Matrix4f *t){" << endl;
        transform_code_begin();
        out << "glRotatef(90,1,0,0);" << endl;
        gen_icocylinder_wire(1);
        transform_code_end();
        out << "}" << endl << endl;

                // CAPSULE
        out << "void " << CLASS << "::wire_capsule(float r, float l, Material *mat, Matrix4f *t){" << endl;
        transform_code_begin();
        out << "glRotatef(90,1,0,0);" << endl;
        gen_icocapsule_wire(1);
        transform_code_end();
        out << "}" << endl << endl;



        cout << "file generated with success!"<< endl;
    } else cout << "Unable to open file" << endl;

    return 0;
}

//--------------------------------------------------------------------------------
//SPHERE
//--------------------------------------------------------------------------------


void gen_sphere(int div) {
    out << "\t//SPHERE DIV " << div << endl;
    out << "\t//PARAM: r : ray" << endl;
    float angi = PI_180*360.0/div;
    float angj = PI_180*360.0/div;
    float ai1,ai2,aj1,aj2,x,y,z;

    material_code();

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
}

//--------------------------------------------------------------------------------
//BOX
//--------------------------------------------------------------------------------

void gen_box() {
    out << "\t//BOX" << endl;
    out << "\t//PARAM: lx : x length / ly : y length / lz : z length" << endl;

    material_code();

    out << "\tfloat lx_2 = lx/2, ly_2 = ly/2, lz_2 = lz/2;" << endl;

    out << "\tglBegin(GL_QUADS);" << endl;
    //front
    out << "\tglNormal3f(0,0,+1);" << endl;
    out << "\tglVertex3f(-lx_2,-ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,-ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,+ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(-lx_2,+ly_2,+lz_2);" << endl;
    //back
    out << "\tglNormal3f(0,0,-1);" << endl;
    out << "\tglVertex3f(-lx_2,-ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(-lx_2,+ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,+ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,-ly_2,-lz_2);" << endl;
    //left
    out << "\tglNormal3f(-1,0,0);" << endl;
    out << "\tglVertex3f(-lx_2,-ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(-lx_2,-ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(-lx_2,+ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(-lx_2,+ly_2,-lz_2);" << endl;
    //right
    out << "\tglNormal3f(+1,0,0);" << endl;
    out << "\tglVertex3f(+lx_2,-ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,+ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,+ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,-ly_2,+lz_2);" << endl;
    //top
    out << "\tglNormal3f(0,+1,0);" << endl;
    out << "\tglVertex3f(-lx_2,+ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(-lx_2,+ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,+ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,+ly_2,-lz_2);" << endl;
    //bottom
    out << "\tglNormal3f(0,-1,0);" << endl;
    out << "\tglVertex3f(-lx_2,-ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,-ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,-ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(-lx_2,-ly_2,+lz_2);" << endl;
    out << "\tglEnd();" << endl;
}

//--------------------------------------------------------------------------------
//ICOSPHERE WIRE
//--------------------------------------------------------------------------------

void icosphere_wire_rec(float x1, float y1, float z1,
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

        icosphere_wire_rec(x12,y12,z12, x23,y23,z23, x31,y31,z31 ,depth-1);
        icosphere_wire_rec(x1,y1,z1, x12,y12,z12, x31,y31,z31 ,depth-1);
        icosphere_wire_rec(x2,y2,z2, x23,y23,z23, x12,y12,z12 ,depth-1);
        icosphere_wire_rec(x3,y3,z3, x31,y31,z31, x23,y23,z23 ,depth-1);
    } else {
        //out << "\tglNormal3f("<<x1<<","<<y1<<","<<z1<<");" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<",r*"<<z1<<");" << endl;

        //out << "\tglNormal3f("<<x2<<","<<y2<<","<<z2<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<",r*"<<z2<<");" << endl;

        //out << "\tglNormal3f("<<x3<<","<<y3<<","<<z3<<");" << endl;
        out << "\tglVertex3f(r*"<<x3<<",r*"<<y3<<",r*"<<z3<<");" << endl;
    }
}

void gen_icosphere_wire(int div) {
    out << "\t//SPHERE DIV " << div << endl;
    out << "\t//PARAM: r : ray" << endl;

    material_code();

    icosphere_wire_rec(0,1,0, 0,0,1, 1,0,0 ,div);
    icosphere_wire_rec(0,1,0, 1,0,0, 0,0,-1 ,div);
    icosphere_wire_rec(0,1,0, 0,0,-1, -1,0,0 ,div);
    icosphere_wire_rec(0,1,0, -1,0,0, 0,0,1 ,div);

    icosphere_wire_rec(0,-1,0, 1,0,0, 0,0,1 ,div);
    icosphere_wire_rec(0,-1,0, 0,0,-1, 1,0,0 ,div);
    icosphere_wire_rec(0,-1,0, -1,0,0, 0,0,-1 ,div);
    icosphere_wire_rec(0,-1,0, 0,0,1, -1,0,0 ,div);
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
        out << "\tglBegin(GL_LINE_LOOP);" << endl;
        out << "\tglNormal3f("<<x1<<","<<y1<<","<<z1<<");" << endl;
        //out << "\tglNormal3f("<<x123<<","<<y123<<","<<z123<<");" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<",r*"<<z1<<");" << endl;
        out << "\tglNormal3f("<<x2<<","<<y2<<","<<z2<<");" << endl;
        //out << "\tglNormal3f("<<x123<<","<<y123<<","<<z123<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<",r*"<<z2<<");" << endl;
        out << "\tglNormal3f("<<x3<<","<<y3<<","<<z3<<");" << endl;
        //out << "\tglNormal3f("<<x123<<","<<y123<<","<<z123<<");" << endl;
        out << "\tglVertex3f(r*"<<x3<<",r*"<<y3<<",r*"<<z3<<");" << endl;
        out << "\tglEnd();" << endl;
    }
}

void gen_icosphere(int div) {
    out << "\t//SPHERE DIV " << div << endl;
    out << "\t//PARAM: r : ray" << endl;

    material_code();

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
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<offset<<"l_2,r*"<<z1<<");" << endl;
        out << "\tglNormal3f("<<x2<<","<<y2<<","<<z2<<");" << endl;
        //out << "\tglNormal3f("<<x123<<","<<y123<<","<<z123<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<offset<<"l_2,r*"<<z2<<");" << endl;
        out << "\tglNormal3f("<<x3<<","<<y3<<","<<z3<<");" << endl;
        //out << "\tglNormal3f("<<x123<<","<<y123<<","<<z123<<");" << endl;
        out << "\tglVertex3f(r*"<<x3<<",r*"<<y3<<offset<<"l_2,r*"<<z3<<");" << endl;
    }
}

void icocapsule_center_rec(float x1, float y1, float z1,
                           float x2, float y2, float z2,
                           int depth ) {
    if(depth>0) {
        float x12 = (x1+x2);
        float y12 = (y1+y2);
        float z12 = (z1+z2);
        float d = sqrt( (x12*x12) + (y12*y12) + (z12*z12) );
        x12/=d;
        y12/=d;
        z12/=d;

        icocapsule_center_rec(x1, y1, z1, x12, y12, z12, depth-1);
        icocapsule_center_rec(x12, y12, z12, x2, y2, z2, depth-1);
    } else {
        out << "\tglNormal3f("<<x1<<","<<y1<<","<<z1<<");" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<"-l_2,r*"<<z1<<");" << endl;
        out << "\tglNormal3f("<<x2<<","<<y2<<","<<z2<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<"-l_2,r*"<<z2<<");" << endl;
        out << "\tglNormal3f("<<x2<<","<<y2<<","<<z2<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<"+l_2,r*"<<z2<<");" << endl;
        out << "\tglNormal3f("<<x1<<","<<y1<<","<<z1<<");" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<"+l_2,r*"<<z1<<");" << endl;
    }
}

void gen_icocapsule(int div) {
    out << "\t//SPHERE DIV " << div << endl;
    out << "\t//PARAM: r : ray / l : length" << endl;

    material_code();

    out << "\tfloat l_2 = l/2;" << endl;

    out << "\tglBegin(GL_TRIANGLES);" << endl;
    icocapsule_pole_rec(0,1,0, 0,0,1, 1,0,0 ,true,div);
    icocapsule_pole_rec(0,1,0, 1,0,0, 0,0,-1 ,true,div);
    icocapsule_pole_rec(0,1,0, 0,0,-1, -1,0,0 ,true,div);
    icocapsule_pole_rec(0,1,0, -1,0,0, 0,0,1 ,true,div);

    icocapsule_pole_rec(0,-1,0, 1,0,0, 0,0,1 ,false,div);
    icocapsule_pole_rec(0,-1,0, 0,0,-1, 1,0,0 ,false,div);
    icocapsule_pole_rec(0,-1,0, -1,0,0, 0,0,-1 ,false,div);
    icocapsule_pole_rec(0,-1,0, 0,0,1, -1,0,0 ,false,div);
    out << "\tglEnd();" << endl;

    out << "\tglBegin(GL_QUADS);" << endl;
    icocapsule_center_rec(1,0,0, 0,0,-1, div);
    icocapsule_center_rec(0,0,-1, -1,0,0, div);
    icocapsule_center_rec(-1,0,0, 0,0,1, div);
    icocapsule_center_rec(0,0,1, 1,0,0, div);
    out << "\tglEnd();" << endl;
}

//--------------------------------------------------------------------------------
// WIRE ICOCAPSULE
//--------------------------------------------------------------------------------

void icocapsule_pole_rec_wire(float x1, float y1, float z1,
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

        icocapsule_pole_rec_wire(x12,y12,z12, x23,y23,z23, x31,y31,z31 ,top,depth-1);
        icocapsule_pole_rec_wire(x1,y1,z1, x12,y12,z12, x31,y31,z31 ,top,depth-1);
        icocapsule_pole_rec_wire(x2,y2,z2, x23,y23,z23, x12,y12,z12 ,top,depth-1);
        icocapsule_pole_rec_wire(x3,y3,z3, x31,y31,z31, x23,y23,z23 ,top,depth-1);
    } else {
        char offset;
        if(top)
            offset = '+';
        else
            offset = '-';

        out << "\tglBegin(GL_LINE_LOOP);" << endl;
        //out << "\tglNormal3f("<<x1<<","<<y1<<","<<z1<<");" << endl;
        //out << "\tglNormal3f("<<x123<<","<<y123<<","<<z123<<");" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<offset<<"l_2,r*"<<z1<<");" << endl;
        //out << "\tglNormal3f("<<x2<<","<<y2<<","<<z2<<");" << endl;
        //out << "\tglNormal3f("<<x123<<","<<y123<<","<<z123<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<offset<<"l_2,r*"<<z2<<");" << endl;
        //out << "\tglNormal3f("<<x3<<","<<y3<<","<<z3<<");" << endl;
        //out << "\tglNormal3f("<<x123<<","<<y123<<","<<z123<<");" << endl;
        out << "\tglVertex3f(r*"<<x3<<",r*"<<y3<<offset<<"l_2,r*"<<z3<<");" << endl;

        out << "\tglEnd();" << endl;
    }
}

void icocapsule_center_rec_wire(float x1, float y1, float z1,
                           float x2, float y2, float z2,
                           int depth ) {
    if(depth>0) {
        float x12 = (x1+x2);
        float y12 = (y1+y2);
        float z12 = (z1+z2);
        float d = sqrt( (x12*x12) + (y12*y12) + (z12*z12) );
        x12/=d;
        y12/=d;
        z12/=d;

        icocapsule_center_rec_wire(x1, y1, z1, x12, y12, z12, depth-1);
        icocapsule_center_rec_wire(x12, y12, z12, x2, y2, z2, depth-1);
    } else {
        out << "\tglBegin(GL_LINE_LOOP);" << endl;

        //out << "\tglNormal3f("<<x1<<","<<y1<<","<<z1<<");" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<"-l_2,r*"<<z1<<");" << endl;
        //out << "\tglNormal3f("<<x2<<","<<y2<<","<<z2<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<"-l_2,r*"<<z2<<");" << endl;
        //out << "\tglNormal3f("<<x2<<","<<y2<<","<<z2<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<"+l_2,r*"<<z2<<");" << endl;
        //out << "\tglNormal3f("<<x1<<","<<y1<<","<<z1<<");" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<"+l_2,r*"<<z1<<");" << endl;

        out << "\tglEnd();" << endl;
    }
}

void gen_icocapsule_wire(int div) {
    out << "\t//SPHERE DIV " << div << endl;
    out << "\t//PARAM: r : ray / l : length" << endl;

    material_code();

    out << "\tfloat l_2 = l/2;" << endl;

    icocapsule_pole_rec_wire(0,1,0, 0,0,1, 1,0,0 ,true,div);
    icocapsule_pole_rec_wire(0,1,0, 1,0,0, 0,0,-1 ,true,div);
    icocapsule_pole_rec_wire(0,1,0, 0,0,-1, -1,0,0 ,true,div);
    icocapsule_pole_rec_wire(0,1,0, -1,0,0, 0,0,1 ,true,div);

    icocapsule_pole_rec_wire(0,-1,0, 1,0,0, 0,0,1 ,false,div);
    icocapsule_pole_rec_wire(0,-1,0, 0,0,-1, 1,0,0 ,false,div);
    icocapsule_pole_rec_wire(0,-1,0, -1,0,0, 0,0,-1 ,false,div);
    icocapsule_pole_rec_wire(0,-1,0, 0,0,1, -1,0,0 ,false,div);

    icocapsule_center_rec_wire(1,0,0, 0,0,-1, div);
    icocapsule_center_rec_wire(0,0,-1, -1,0,0, div);
    icocapsule_center_rec_wire(-1,0,0, 0,0,1, div);
    icocapsule_center_rec_wire(0,0,1, 1,0,0, div);
}

//--------------------------------------------------------------------------------
//CYLINDER
//--------------------------------------------------------------------------------

void icocylinder_rec(float x1, float y1, float z1,
                     float x2, float y2, float z2,
                     int depth ) {
    if(depth>0) {
        float x12 = (x1+x2);
        float y12 = (y1+y2);
        float z12 = (z1+z2);
        float d = sqrt( (x12*x12) + (y12*y12) + (z12*z12) );
        x12/=d;
        y12/=d;
        z12/=d;

        icocylinder_rec(x1, y1, z1, x12, y12, z12, depth-1);
        icocylinder_rec(x12, y12, z12, x2, y2, z2, depth-1);
    } else {
        out << "\tglBegin(GL_QUADS);" << endl;
        out << "\tglNormal3f("<<x1<<","<<y1<<","<<z1<<");" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<"-l_2,r*"<<z1<<");" << endl;
        out << "\tglNormal3f("<<x2<<","<<y2<<","<<z2<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<"-l_2,r*"<<z2<<");" << endl;
        out << "\tglNormal3f("<<x2<<","<<y2<<","<<z2<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<"+l_2,r*"<<z2<<");" << endl;
        out << "\tglNormal3f("<<x1<<","<<y1<<","<<z1<<");" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<"+l_2,r*"<<z1<<");" << endl;
        out << "\tglEnd();" << endl;

        out << "\tglBegin(GL_TRIANGLES);" << endl;
        out << "\tglNormal3f(0,-1,0);" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<"-l_2,r*"<<z2<<");" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<"-l_2,r*"<<z1<<");" << endl;
        out << "\tglVertex3f(0,-l_2,0);" << endl;

        out << "\tglNormal3f(0,+1,0);" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<"+l_2,r*"<<z1<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<"+l_2,r*"<<z2<<");" << endl;
        out << "\tglVertex3f(0,+l_2,0);" << endl;
        out << "\tglEnd();" << endl;
    }
}

void gen_icocylinder(int div) {
    out << "\t//CYLINDER DIV " << div << endl;
    out << "\t//PARAM: r : ray / l : length" << endl;

    material_code();

    out << "\tfloat l_2 = l/2;" << endl;

    icocylinder_rec(1,0,0, 0,0,-1, div);
    icocylinder_rec(0,0,-1, -1,0,0, div);
    icocylinder_rec(-1,0,0, 0,0,1, div);
    icocylinder_rec(0,0,1, 1,0,0, div);
}

//--------------------------------------------------------------------------------
// CHESS PLANE
//--------------------------------------------------------------------------------

void gen_chess_plane(int div) {
    out << "\t//PLANE DIV " << div << endl;
    out << "\t//PARAM: s : size" << endl;

    material_code();

    out << "\tglBegin(GL_QUADS);" << endl;
    out << "\tglNormal3f(0,1,0);" << endl;

    for(int x=0; x<div; x++) {
        for(int z=0; z<div; z++) {
            if( ((x+z)%2)==0 ) {
                out << "\tglVertex3f(("<<((float)x)/div<<")*s,0,("<<((float)z)/div<<")*s);" << endl;
                out << "\tglVertex3f(("<<((float)x)/div<<")*s,0,("<<((float)z+1.0)/div<<")*s);" << endl;
                out << "\tglVertex3f(("<<((float)x+1.0)/div<<")*s,0,("<<((float)z+1.0)/div<<")*s);" << endl;
                out << "\tglVertex3f(("<<((float)x+1.0)/div<<")*s,0,("<<((float)z)/div<<")*s);" << endl;
                out << endl;
            }
        }
    }
    out << "\tglEnd();" << endl;

    material_code(false,true);
    out << "\tglBegin(GL_QUADS);" << endl;
    out << "\tglNormal3f(0,1,0);" << endl;

    for(int x=0; x<div; x++) {
        for(int z=0; z<div; z++) {
            if( ((x+z)%2)!=0 ) {
                out << "\tglVertex3f(("<<((float)x)/div<<")*s,0,("<<((float)z)/div<<")*s);" << endl;
                out << "\tglVertex3f(("<<((float)x)/div<<")*s,0,("<<((float)z+1.0)/div<<")*s);" << endl;
                out << "\tglVertex3f(("<<((float)x+1.0)/div<<")*s,0,("<<((float)z+1.0)/div<<")*s);" << endl;
                out << "\tglVertex3f(("<<((float)x+1.0)/div<<")*s,0,("<<((float)z)/div<<")*s);" << endl;
                out << endl;
            }
        }
    }
    out << "\tglEnd();" << endl;
}

//--------------------------------------------------------------------------------
//FLOOR
//--------------------------------------------------------------------------------

void gen_chess_floor() {
    out << "\t//PARAM: s : size" << endl;

    material_code();
    out << "\tglBegin(GL_QUADS);" << endl;
    out << "\tglNormal3f(0,1,0);" << endl;

    float a = 20.0;
    float b = 20.0;

    for(int i=0; i<a; i++) {
        for(int j=0; j<b; j++) {
            if( (i+j)%2 == 0 ) {
                out << "\tglVertex3f(s*("<<(2*((i)/a))-1<<"),0,s*("<<(2*((j)/b))-1<<"));" << endl;
                out << "\tglVertex3f(s*("<<(2*((i)/a))-1<<"),0,s*("<<(2*((j+1)/b))-1<<"));" << endl;
                out << "\tglVertex3f(s*("<<(2*((i+1)/a))-1<<"),0,s*("<<(2*((j+1)/b))-1<<"));" << endl;
                out << "\tglVertex3f(s*("<<(2*((i+1)/a))-1<<"),0,s*("<<(2*((j)/b))-1<<"));" << endl;
            }
        }
    }

    out << "\tglEnd();" << endl;

    out << endl << "\tmat->glHalf();" << endl;
    out << "\tglBegin(GL_QUADS);" << endl;
    out << "\tglNormal3f(0,1,0);" << endl;

    for(int i=0; i<a; i++) {
        for(int j=0; j<b; j++) {
            if( (i+j)%2 != 0 ) {
                out << "\tglVertex3f(s*("<<(2*((i)/a))-1<<"),0,s*("<<(2*((j)/b))-1<<"));" << endl;
                out << "\tglVertex3f(s*("<<(2*((i)/a))-1<<"),0,s*("<<(2*((j+1)/b))-1<<"));" << endl;
                out << "\tglVertex3f(s*("<<(2*((i+1)/a))-1<<"),0,s*("<<(2*((j+1)/b))-1<<"));" << endl;
                out << "\tglVertex3f(s*("<<(2*((i+1)/a))-1<<"),0,s*("<<(2*((j)/b))-1<<"));" << endl;
            }
        }
    }

    out << "\tglEnd();" << endl;
}

//--------------------------------------------------------------------------------
// CIRCLE
//--------------------------------------------------------------------------------

void gen_circle() {
    out << "\t//PARAM: r : ray" << endl;

    material_code();
    out << "\tglBegin(GL_LINE_LOOP);" << endl;
    out << "\tglNormal3f(0,0,1);" << endl;


    for(int i=0; i<36; i++) {
        out << "\tglVertex3f(r*("<<cos(i*M_PI/18)<<"),r*("<<sin(i*M_PI/18)<<"),0);" << endl;
    }
    out << "\tglVertex3f(r*("<<cos(0*M_PI/18)<<"),r*("<<sin(0*M_PI/18)<<"),0);" << endl;

    out << "\tglEnd();" << endl;
}

//--------------------------------------------------------------------------------
// VECTOR
//--------------------------------------------------------------------------------

void gen_vector() {

    out << "\tglPushMatrix(); " << endl;

    out << "\tMatrix4f tt;" << endl;
    out << "\ttt.setRotation( vector , Vector3f(0,1,0) );" << endl;
    out << "\ttt.translate( pos );" << endl;

    out << "\tfloat transform[16]; " << endl;
    out << "\ttt.get(transform); " << endl;

    out << "\tglMultMatrixf(transform); " << endl;
    material_code();

    out << "\tfloat r = vector.size();" << endl;

    out << "\tglBegin(GL_TRIANGLES);" << endl;

    int div = 18;

    for(int i=0;i<360/div;i++){
    out << "\tglNormal3f( ("<< sin( div*(i+0.5)*(M_PI/180)) <<") , ("<< cos( div*(i+0.5)*(M_PI/180)) <<"), 0);" << endl;
    out << "\tglVertex3f(0,0,0);" << endl;

    out << "\tglNormal3f( ("<< sin(div*(i+1)*(M_PI/180)) <<") , ("<< cos( div*(i+1)*(M_PI/180)) <<"), 0);" << endl;
    out << "\tglVertex3f(r*("<< 0.05*sin( div*(i+1)*(M_PI/180) ) <<"),r*("<< 0.05*cos( div*(i+1)*(M_PI/180) ) <<"),-r*("<< 0.8 <<"));" << endl;

    out << "\tglNormal3f( ("<< sin(div*(i)*(M_PI/180)) <<") , ("<< cos( div*(i)*(M_PI/180)) <<"), 0);" << endl;
    out << "\tglVertex3f(r*("<< 0.05*sin( div*(i)*(M_PI/180) ) <<"),r*("<< 0.05*cos( div*(i)*(M_PI/180) ) <<"),-r*("<< 0.8 <<"));" << endl;


    out << "\tglNormal3f( ("<< sin(div*(i+0.5)*(M_PI/180)) <<") , ("<< cos( div*(i+0.5)*(M_PI/180)) <<"), 0);" << endl;
    out << "\tglVertex3f(0,0,-r);" << endl;

    out << "\tglNormal3f( ("<< sin( div*(i)*(M_PI/180)) <<") , ("<< cos( div*(i)*(M_PI/180)) <<"), 0);" << endl;
    out << "\tglVertex3f(r*("<< 0.1*sin( div*(i)*(M_PI/180) ) <<"),r*("<< 0.1*cos( div*(i)*(M_PI/180) ) <<"),-r*("<< 0.8 <<"));" << endl;

    out << "\tglNormal3f( ("<< sin( div*(i+1)*(M_PI/180)) <<") , ("<< cos( div*(i+1)*(M_PI/180)) <<"), 0);" << endl;
    out << "\tglVertex3f(r*("<< 0.1*sin( div*(i+1)*(M_PI/180) ) <<"),r*("<< 0.1*cos( div*(i+1)*(M_PI/180) ) <<"),-r*("<< 0.8 <<"));" << endl;
    }

    out << "\tglEnd();" << endl;

    out << "\tglBegin(GL_QUADS);" << endl;
    out << "\tglNormal3f( 0, 0, 1);" << endl;
    for(int i=0;i<360/div;i++){
    out << "\tglVertex3f(r*("<< 0.05*sin( div*(i+1)*(M_PI/180) ) <<"),r*("<< 0.05*cos( div*(i+1)*(M_PI/180) ) <<"),-r*("<< 0.8 <<"));" << endl;
    out << "\tglVertex3f(r*("<< 0.1*sin( div*(i+1)*(M_PI/180) ) <<"),r*("<< 0.1*cos( div*(i+1)*(M_PI/180) ) <<"),-r*("<< 0.8 <<"));" << endl;
    out << "\tglVertex3f(r*("<< 0.1*sin( div*(i)*(M_PI/180) ) <<"),r*("<< 0.1*cos( div*(i)*(M_PI/180) ) <<"),-r*("<< 0.8 <<"));" << endl;
    out << "\tglVertex3f(r*("<< 0.05*sin( div*(i)*(M_PI/180) ) <<"),r*("<< 0.05*cos( div*(i)*(M_PI/180) ) <<"),-r*("<< 0.8 <<"));" << endl;

    }
    out << "\tglEnd();" << endl;

    out << "\tglPopMatrix(); " << endl;
}

//--------------------------------------------------------------------------------
//BOX WIRE
//--------------------------------------------------------------------------------

void gen_box_wire() {
    out << "\t//BOX INVERSE" << endl;
    out << "\t//PARAM: lx : x length / ly : y length / lz : z length" << endl;

    material_code(true,false);

    out << "\tfloat lx_2 = (lx/2), ly_2 = (ly/2), lz_2 = (lz/2);" << endl;

    out << "\tglBegin(GL_LINE_LOOP);" << endl;
    //front
    //out << "\tglNormal3f(0,0,+1);" << endl;
    out << "\tglVertex3f(-lx_2,-ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,-ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,+ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(-lx_2,+ly_2,+lz_2);" << endl;
    out << "\tglEnd();" << endl;
    out << "\tglBegin(GL_LINE_LOOP);" << endl;
    //back
    //out << "\tglNormal3f(0,0,-1);" << endl;
    out << "\tglVertex3f(-lx_2,-ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(-lx_2,+ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,+ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,-ly_2,-lz_2);" << endl;
    out << "\tglEnd();" << endl;
    out << "\tglBegin(GL_LINE_LOOP);" << endl;
    //left
    //out << "\tglNormal3f(-1,0,0);" << endl;
    out << "\tglVertex3f(-lx_2,-ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(-lx_2,-ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(-lx_2,+ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(-lx_2,+ly_2,-lz_2);" << endl;
    out << "\tglEnd();" << endl;
    out << "\tglBegin(GL_LINE_LOOP);" << endl;
    //right
    //out << "\tglNormal3f(+1,0,0);" << endl;
    out << "\tglVertex3f(+lx_2,-ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,+ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,+ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,-ly_2,+lz_2);" << endl;
    out << "\tglEnd();" << endl;
    out << "\tglBegin(GL_LINE_LOOP);" << endl;
    //top
    //out << "\tglNormal3f(0,+1,0);" << endl;
    out << "\tglVertex3f(-lx_2,+ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(-lx_2,+ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,+ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,+ly_2,-lz_2);" << endl;
    out << "\tglEnd();" << endl;
    out << "\tglBegin(GL_LINE_LOOP);" << endl;
    //bottom
    //out << "\tglNormal3f(0,-1,0);" << endl;
    out << "\tglVertex3f(-lx_2,-ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,-ly_2,-lz_2);" << endl;
    out << "\tglVertex3f(+lx_2,-ly_2,+lz_2);" << endl;
    out << "\tglVertex3f(-lx_2,-ly_2,+lz_2);" << endl;
    out << "\tglEnd();" << endl;
}

//--------------------------------------------------------------------------------
// WIRE CYLINDER
//--------------------------------------------------------------------------------

void wire_icocylinder_rec(float x1, float y1, float z1,
                     float x2, float y2, float z2,
                     int depth ) {
    if(depth>0) {
        float x12 = (x1+x2);
        float y12 = (y1+y2);
        float z12 = (z1+z2);
        float d = sqrt( (x12*x12) + (y12*y12) + (z12*z12) );
        x12/=d;
        y12/=d;
        z12/=d;

        wire_icocylinder_rec(x1, y1, z1, x12, y12, z12, depth-1);
        wire_icocylinder_rec(x12, y12, z12, x2, y2, z2, depth-1);
    } else {
        out << "\tglBegin(GL_LINE_LOOP);" << endl;
        //out << "\tglNormal3f("<<x1<<","<<y1<<","<<z1<<");" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<"-l_2,r*"<<z1<<");" << endl;
        //out << "\tglNormal3f("<<x2<<","<<y2<<","<<z2<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<"-l_2,r*"<<z2<<");" << endl;
        //out << "\tglNormal3f("<<x2<<","<<y2<<","<<z2<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<"+l_2,r*"<<z2<<");" << endl;
        //out << "\tglNormal3f("<<x1<<","<<y1<<","<<z1<<");" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<"+l_2,r*"<<z1<<");" << endl;
        out << "\tglEnd();" << endl;

        out << "\tglBegin(GL_LINE_LOOP);" << endl;
        //out << "\tglNormal3f(0,-1,0);" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<"-l_2,r*"<<z2<<");" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<"-l_2,r*"<<z1<<");" << endl;
        out << "\tglVertex3f(0,-l_2,0);" << endl;

        //out << "\tglNormal3f(0,+1,0);" << endl;
        out << "\tglVertex3f(r*"<<x1<<",r*"<<y1<<"+l_2,r*"<<z1<<");" << endl;
        out << "\tglVertex3f(r*"<<x2<<",r*"<<y2<<"+l_2,r*"<<z2<<");" << endl;
        out << "\tglVertex3f(0,+l_2,0);" << endl;
        out << "\tglEnd();" << endl;
    }
}

void gen_icocylinder_wire(int div) {
    out << "\t//CYLINDER DIV " << div << endl;
    out << "\t//PARAM: r : ray / l : length" << endl;

    material_code();

    out << "\tfloat l_2 = l/2;" << endl;

    icocylinder_rec(1,0,0, 0,0,-1, div);
    icocylinder_rec(0,0,-1, -1,0,0, div);
    icocylinder_rec(-1,0,0, 0,0,1, div);
    icocylinder_rec(0,0,1, 1,0,0, div);
}

//--------------------------------------------------------------------------------
//SHAPE
//--------------------------------------------------------------------------------

void gen_shape() {
}
