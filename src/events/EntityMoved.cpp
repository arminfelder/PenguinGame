//
// Created by armin on 29.12.18.
//

#include "EntityMoved.h"

using namespace Events;
EntityMoved::EntityMoved(int pEntityId, Direction pDirection):Event(EventTypes::EntityMoved),mEntityId(pEntityId),mDirection(pDirection) {

}
