//
// Created by jérémie on 11/12/2024.
//

#include "Vector2D.h"

Vector2D::Vector2D(int x, int y) {
  this->x = x;
  this->y = y;
}

int Vector2D::getSquaredLength() {
  return this->x * this->x + this->y * this-> y;
}

int Vector2D::getLength() {
  return sqrt(this->getSquaredLength());
}