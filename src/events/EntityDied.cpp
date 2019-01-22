//
// Created by armin on 22.01.19.
//

#include "EntityDied.h"

using namespace Events;
EntityDied::EntityDied(int pEntity, int pOrigHealth):Event(EventTypes::EntityDied),mEntity(pEntity),mOrigHealth(pOrigHealth) {

}
