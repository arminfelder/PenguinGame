#include "MoveAbleComponent.h"

Components::MoveAbleComponent::MoveAbleComponent() {

}

Components::MoveAbleComponent::MoveAbleComponent(bool pRight, bool pDown, bool pLeft, bool pTop):canMoveRight(pRight),canMoveDown(pDown),canMoveLeft(pLeft),canMoveUp(pTop) {

}
