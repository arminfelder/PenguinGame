#include "Dimension.h"

Dimension::Dimension(int xDimension, int yDimension) {
    this->setDimension(xDimension, yDimension);
}

Dimension::Dimension() = default;

void Dimension::setDimension(int xDimension, int yDimension) {
    this->xDimension = xDimension;
    this->yDimension = yDimension;
}

int Dimension::getYDimension() {
    return this->yDimension;
}

int Dimension::getXDimension() {
    return this->xDimension;
}
