#include "position.h"

position::position(int xPosition, int yPosition) {
    this->setPosition(xPosition, yPosition);
}

void position::setPosition(int xPosition, int yPosition) {
    this->xPosition = xPosition;
    this->yPosition = yPosition;
}

int position::getYPosition() {
    return this->yPosition;
}

int position::getXPosition() {
    return this->xPosition;
}
