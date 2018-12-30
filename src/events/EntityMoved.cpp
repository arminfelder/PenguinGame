//
// Created by armin on 29.12.18.
//

#include "EntityMoved.h"

using namespace Events;
EntityMoved::EntityMoved(int pEntityId):Event(EventTypes::EntityMoved),mEntityId(pEntityId) {

}
