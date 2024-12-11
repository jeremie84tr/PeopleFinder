//
// Created by jérémie on 11/12/2024.
//

#include "Vector3D.h"

Vector3D::Vector3D(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

int Vector3D::getSquaredLength() {
    return this->x * this->x + this->y * this-> y + this->z * this->z;
}

int Vector3D::getLength() {
    return sqrt(this->getSquaredLength());
}