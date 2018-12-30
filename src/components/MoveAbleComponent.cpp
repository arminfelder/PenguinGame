//
// Created by armin on 30.12.18.
//

#include "MoveAbleComponent.h"

Components::MoveAbleComponent::MoveAbleComponent() {

}

Components::MoveAbleComponent::MoveAbleComponent(bool pRight, bool pDown, bool pLeft, bool pTop):canMoveRight(pRight),canMoveDown(pDown),canMoveLeft(pLeft),canMoveUp(pTop) {

}
