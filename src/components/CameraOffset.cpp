#include "CameraOffset.h"

using namespace Components;
CameraOffset::CameraOffset(int pXOffset, int pYOffset): xOffset (pXOffset), yOffset (pYOffset)  {}

int CameraOffset::getXOffset() const {
    return xOffset;
}

void CameraOffset::setXOffset(int xOffset) {
    CameraOffset::xOffset = xOffset;
}

int CameraOffset::getYOffset() const {
    return yOffset;
}

void CameraOffset::setYOffset(int yOffset) {
    CameraOffset::yOffset = yOffset;
}
