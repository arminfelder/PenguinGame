#include <iostream>
#include "Entity.h"
#include "../position.h"
#include "../Dimension.h"

using namespace Entities;

Entity::Entity(int pId, entityTypes pType):mId(pId),mEntityType(pType) {

}

int Entity::getId() const {
    return mId;
}

entityTypes Entity::getType() {
    return mEntityType;
}
