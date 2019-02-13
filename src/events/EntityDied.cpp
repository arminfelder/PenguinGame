//
// Created by armin on 22.01.19.
//

#include "EntityDied.h"

using namespace Events;
EntityDied::EntityDied(int pEntity, int pOrigHealth, SDL_Point pPosition, const std::shared_ptr<Components::Inventory> &pInventory):Event(EventTypes::EntityDied),mEntity(pEntity),mOrigHealth(pOrigHealth),mInventory(pInventory),mPosition(pPosition) {

}
