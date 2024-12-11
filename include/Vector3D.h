//
// Created by jérémie on 11/12/2024.
//

#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <math.h>



class Vector3D {
    int x;
    int y;
    int z;

    Vector3D(int,int,int);
    int getSquaredLength();
    int getLength();
};



#endif //VECTOR3D_H
