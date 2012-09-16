#include "matrix4f.h"

#include <cstring>

Matrix4f::Matrix4f()
{
}

void Matrix4f::set(int position, float value)
{
    if(position >= 0 and position < 16){
        matrix[position] = value;
    }
}

void Matrix4f::get(float output[]) const
{
    memcpy(output, matrix, 16*sizeof(float));
}

float Matrix4f::get(int index) const
{
    if(index > 0 and index < 16){
        return matrix[index];
    }else{
        return 0;
    }
}

#ifdef DEBUG_MODE
#include <iostream>
using namespace std;

void Matrix4f::stdPrint()
{
    cout << "==Matrix=="<< endl;
    for(int i=0;i<4;i++){
        cout << matrix[0+i] << " " << matrix[4+i] << " " << matrix[8+i] << " " << matrix[12+i] << endl;
    }
    cout << "=========="<< endl;
}
#endif
