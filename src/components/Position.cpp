//
// Created by armin on 07.12.18.
//

#include "Position.h"
using namespace Components;

Position::Position(int xPosition, int yPosition) {
    this->setPosition(xPosition, yPosition);
}

void Position::setPosition(int xPosition, int yPosition) {
    mX = xPosition;
    mY = yPosition;
}

int Position::getYPosition() {
    return mY;
}

int Position::getXPosition() {
    return mX;
}
