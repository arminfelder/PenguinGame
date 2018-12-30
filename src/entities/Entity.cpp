#include <iostream>
#include "Entity.h"
#include "../position.h"
#include "../Dimension.h"

using namespace Entities;

Entity::Entity(int id) {

}

int Entity::getId() const {
    return mId;
}
