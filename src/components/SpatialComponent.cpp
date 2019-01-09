//
// Created by armin on 27.12.18.
//

#include "SpatialComponent.h"

Components::SpatialComponent::SpatialComponent(int pPositionX, int pPositionY,bool pMoveWithMap) {
    mPositionX = pPositionX;
    mPositionY = pPositionY;
    moveWithMap = pMoveWithMap;
}
