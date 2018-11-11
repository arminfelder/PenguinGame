#include "dimension.h"

dimension::dimension(int xDimension, int yDimension) {
    this->setDimension(xDimension, yDimension);
}

dimension::dimension() {}

void dimension::setDimension(int xDimension, int yDimension) {
    this->xDimension = xDimension;
    this->yDimension = yDimension;
}
