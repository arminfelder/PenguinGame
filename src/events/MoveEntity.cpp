//
// Created by armin on 10.01.19.
//

#include "MoveEntity.h"

using namespace Events;
MoveEntity::MoveEntity(int pEntityId ,int pX, int pY):Event(Events::EventTypes::MoveEntity),mEntityId(pEntityId),mX(pX),mY(pY) {

}
