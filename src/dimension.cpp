#include "dimension.h"

dimension::dimension(int xDimension, int yDimension) {
    this->setDimension(xDimension, yDimension);
}

dimension::dimension() = default;

void dimension::setDimension(int xDimension, int yDimension) {
    this->xDimension = xDimension;
    this->yDimension = yDimension;
}

int dimension::getYDimension() {
    return this->yDimension;
}

int dimension::getXDimension() {
    return this->xDimension;
}
