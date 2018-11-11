#include "entityController.h"

void entityController::createEntity(int health, class position *position, class dimension *dimension) {
    auto * entity = new class entity(health, position, dimension);
    entities.push_back(entity);
}

void entityController::printEntities() {
    for (class entity* entity : entities) {
        entity->print();
    }
}
