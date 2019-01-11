

#include "SpatialComponent.h"

Components::SpatialComponent::SpatialComponent(int pPositionX, int pPositionY,bool pMoveWithMap) {
    mPositionX = pPositionX;
    mPositionY = pPositionY;
    moveWithMap = pMoveWithMap;
}
