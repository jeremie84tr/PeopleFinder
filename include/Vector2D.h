//
// Created by jérémie on 11/12/2024.
// This class is a vector2D (Because I want to make it myself)
//

#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <math.h>


class Vector2D {
  int x;
  int y;

  Vector2D(int,int);
  int getSquaredLength();
  int getLength();
};



#endif //VECTOR2D_H
