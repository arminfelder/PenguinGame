#include <iostream>
#include "Entity.h"

using namespace Entities;

Entity::Entity(int pId, entityTypes pType):mId(pId),mEntityType(pType) {

}

int Entity::getId() const {
    return mId;
}

entityTypes Entity::getType() {
    return mEntityType;
}
