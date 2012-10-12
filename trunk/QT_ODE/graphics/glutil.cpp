#include "glutil.h"

#include <QtOpenGL>

void GLUtil::glSphereBillBoard(){
    float matrix4f[16];

    glGetFloatv(GL_MODELVIEW_MATRIX , matrix4f);
    for(int i=0; i<3; i++ ){
        for(int j=0; j<3; j++ ) {
            if ( i==j )
                matrix4f[i*4+j] = 1.0;
            else
                matrix4f[i*4+j] = 0.0;
        }
    }
    glLoadMatrixf(matrix4f);
}
